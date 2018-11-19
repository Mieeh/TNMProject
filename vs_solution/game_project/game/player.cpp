#include"include\player.h"

#include"include/constants.h"
#include"include/combat.h"

#include"../engine/include/bear_game.h"
#include"../engine/include/game_systems.h"
#include"../engine/include/enemy.h"

#include<window/event.h>
#include<window/GLFW_event.h>
using namespace bear;

#include<random>

Player* Player::instance = nullptr;

Player::Player() : player_anim(), player_ui()
{
	entity.renderable.m_TextureName = "runningDown3";
	entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE)*PLAYER_SIZE;
	entity.renderable.m_Layer = LAYER3;
}

std::string Player::get_random_footstep(unsigned int number_of_footsteps)
{
	if (last_played_footstep == "footstep1")
		return "footstep2";
	else
		return "footstep1";
}

void Player::on_event(Event & event)
{					
	if (event.type == EventType::KeyPressed) {
		// Make sure the player is idle before we move/perform something!
		if (player_state == PlayerStates::IDLE) {
			if (event.key == engine->config_manager->key_map.at("MOVE_RIGHT"))
				move_player(PlayerMoveDirection::RIGHT);
			else if (event.key == engine->config_manager->key_map.at("MOVE_LEFT"))
				move_player(PlayerMoveDirection::LEFT);
			else if (event.key == engine->config_manager->key_map.at("MOVE_DOWN"))
				move_player(PlayerMoveDirection::DOWN);
			else if (event.key == engine->config_manager->key_map.at("MOVE_UP"))
				move_player(PlayerMoveDirection::UP);

			if (event.key == engine->config_manager->key_map.at("INTERACT2")) { // 'e' by default
				handle_item_use();
			}
		}
		else if (player_state == PlayerStates::DEAD) {
			if (event.key == Key::X) {
				reset_after_death();
			}
		}
	}
}

void Player::update(float dt)
{	
	// Update the animation object
	entity.renderable.m_TextureName = player_anim.update(player_state, move_direction, dt);

	// What're we doing?
	switch (player_state) {
	case PlayerStates::IDLE:
		idle_player_state_control();
		break;
	case PlayerStates::IN_TRANSIT:
		move_player_state_control(move_direction, dt);
		break;
	case PlayerStates::INTRO:
		intro_player(dt);
		break;
	case PlayerStates::OUTRO:
		outro_player(dt);
		break;
	case PlayerStates::DEAD:
		death_panel.increaseOffset(dt);

		graphics::Shader* fbShader = ResourceManager::Instance()->GetShader("framebuffer_shader");
		fbShader->enable();
		fbShader->setUniformFloat("offset", death_panel.offset);
		fbShader->disable();
		break;
	}
}		

void Player::render()
{
	player_ui.render_player_hp();

	engine->graphics_manager->draw(entity);

	// Dead? render the death panel if we are!
	if (player_state == PlayerStates::DEAD) {
		// We dead boy
	}
}

void Player::move_player(int move_direction_enum)
{
	core::Vector2i new_tile_position = tile_position + move_directions[move_direction_enum];
	int new_tile_value = engine->level_manager->current_level->get_level_content().tile_map.at(new_tile_position.y).at(new_tile_position.x);

	// We trying to transit to a floor?
	if (is_floor(new_tile_value)) {
		// Set the player to be in transit!
		player_state = PlayerStates::IN_TRANSIT;
		move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

		core::Vector2i dir = move_directions[move_direction_enum];
		tile_position += dir;
		world_position = ((core::Vector2f)tile_position * TILE_SIZE) + PLAYER_OFFSET;

		// Walk SFX
		last_played_footstep = get_random_footstep(2);
		
		engine->sound_manager->add_delayed_sfx(last_played_footstep, footstep_delay); // Add delayed sfx to the sound manager

		// Message the level we've moved
		engine->level_manager->current_level->player_moved();
	}
	else if (is_enemy(new_tile_value)) {
		// Get the enemy!
		std::string key = (std::string)new_tile_position;
		EnemyBase& enemy = engine->level_manager->current_level->get_level_content().enemies.at(key);
		resolve_combat(enemy, move_direction_enum);
	}
	else if (is_item(new_tile_value)) {
		std::string key = (std::string)new_tile_position;
		Item& item = engine->level_manager->current_level->get_level_content().items.at(key);
		// Resolve item collision
		resolve_item(item, move_direction_enum);
	}
	else if (new_tile_value == GOAL) {

		goal_trigger = true;

		// Set the player to be in transit!
		player_state = PlayerStates::IN_TRANSIT;
		move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

		core::Vector2i dir = move_directions[move_direction_enum];
		tile_position += dir;
		world_position = ((core::Vector2f)tile_position * TILE_SIZE) + PLAYER_OFFSET;
	}

	// Update the layer
	entity.renderable.m_Layer = LAYER3 + tile_position.y;
}

void Player::intro_player(float dt)
{
	// Move playerdown until we hit the start position
	if (entity.renderable.m_Transform.m_Position.y < world_position.y) {
		entity.renderable.m_Transform.m_Position.y += fall_speed * dt;
		entity.renderable.m_Color.a += 0.0015f*dt;
	}
	else {
		player_state = PlayerStates::IDLE;
		entity.renderable.m_Transform.m_Position = world_position;
		entity.renderable.m_Color.a = 1.0f;
		engine->perform_window_shake(400, 10);
	}
}

void Player::outro_player(float dt)
{
	// Move the player position down until it's faded out
	if (entity.renderable.m_Color.a > 0.0f) {
		// Move and fade
		entity.renderable.m_Color.a -= 0.0015f*dt;
		entity.renderable.m_Transform.m_Position.y += fall_speed * dt;
		// Layering
		entity.renderable.m_Layer = LAYER0;
	}
	else {
		// Reset state
		goal_trigger = false;
		set_player_state(PlayerStates::IDLE);
		// Load new level
		engine->level_manager->setCurrentLevel(engine->level_manager->current_level->next_level_name); // Load the next level
		// Reset layer
		entity.renderable.m_Layer = LAYER3;
	}
}

void Player::set_player_position(const core::Vector2i position)
{
	// Sets the player position (instantly no state logic)
	tile_position = position;
	world_position = ((core::Vector2f)tile_position * TILE_SIZE) + PLAYER_OFFSET;
	entity.renderable.m_Transform.m_Position = world_position;
}

void Player::set_player_state(PlayerStates new_state)
{
	player_state = new_state;
	if (goal_trigger) {
		// Notes(david)s
		//engine->sound_manager->get_sfx("falling")->sf_sound.play();
		player_state = PlayerStates::OUTRO;
	}

	if (new_state == PlayerStates::DEAD) {
		// Tell the graphics_manager we want to enable the death post processing effect
		engine->graphics_manager->set_post_processing_effect(POST_PROCESSING_EFFECTS::BLACK_WHITE_CROSS);
	}
}

void Player::move_player_state_control(PlayerMoveDirection dir, float dt)
{
	switch (dir) {
	case PlayerMoveDirection::RIGHT:
		// Move towards the goal position
		entity.renderable.m_Transform.m_Position.x += move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position!
		if (entity.renderable.m_Transform.m_Position.x >= world_position.x) {
			set_player_state(PlayerStates::IDLE);
			entity.renderable.m_Transform.m_Position = world_position;
		}
		break;
	case PlayerMoveDirection::LEFT:
		entity.renderable.m_Transform.m_Position.x += -move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position!
		if (entity.renderable.m_Transform.m_Position.x <= world_position.x) {
			set_player_state(PlayerStates::IDLE);
			entity.renderable.m_Transform.m_Position = world_position;
		}
		break;
	case PlayerMoveDirection::DOWN:
		entity.renderable.m_Transform.m_Position.y += move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position
		if (entity.renderable.m_Transform.m_Position.y >= world_position.y) {
			set_player_state(PlayerStates::IDLE);
			entity.renderable.m_Transform.m_Position = world_position;
		}
		break;
	case PlayerMoveDirection::UP:
		entity.renderable.m_Transform.m_Position.y += -move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position
		if (entity.renderable.m_Transform.m_Position.y <= world_position.y) {
			set_player_state(PlayerStates::IDLE);
			entity.renderable.m_Transform.m_Position = world_position;
		}
		break;
	}
}

void Player::idle_player_state_control()
{
	// Do idle stuff
}

void Player::play_intro_at(const core::Vector2i position)
{
	player_state = PlayerStates::INTRO;
	tile_position = position;
	world_position = ((core::Vector2f)tile_position * TILE_SIZE) + PLAYER_OFFSET;
	static const int intro_offset = -350; 
	entity.renderable.m_Transform.m_Position = world_position + core::Vector2f(0, intro_offset);

	entity.renderable.m_Color.a = 0.0f;

	// Reset player HP
	hp = 3;
	current_item = nullptr;
}

void Player::resolve_combat(EnemyBase& enemy, int move_direction_enum)
{
	// Check to make sure the enemy isn't already dead!
	if (!enemy.is_dead) {
		// Perform combat with the enemy
		CombatResult combat_result = Combat::perform_combat(enemy);

		if (combat_result == CombatResult::PLAYER_BLOCK_CLASH || combat_result == CombatResult::PLAYER_WEAPON_CLASH) {
			current_item = nullptr;
		}
		// What happend during the combat? 
		switch (combat_result) {
		case CombatResult::ENEMY_DIED:
			enemy.is_dead = true;
			// Enemy dead sfx
			// Notes(david) if the enemy we just killed is not a "bones" enemy then this would be weird?
			// Perhaps have enemy.death_sfx, unique for every type of enemy
			engine->sound_manager->get_sfx("enemy_dead_bones")->sf_sound.play();
			break;
		case CombatResult::PLAYER_DIED:
			set_player_state(PlayerStates::DEAD);
			break;
		case CombatResult::PLAYER_WEAPON_CLASH:
		case CombatResult::PLAYER_BLOCK_CLASH:
		case CombatResult::CLASH:
			// Window shake
			engine->perform_window_shake(100, 3);
			// Enemy hurt sfx
			engine->sound_manager->get_sfx("enemy_hurt")->sf_sound.play();
			break;
		}
	}
	else {
		// Set the player to be in transit!
		player_state = PlayerStates::IN_TRANSIT;
		move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

		core::Vector2i dir = move_directions[move_direction_enum];
		tile_position += dir;
		world_position = ((core::Vector2f)tile_position * TILE_SIZE) + PLAYER_OFFSET;

		// Walk SFX
		last_played_footstep = get_random_footstep(2);
		engine->sound_manager->add_delayed_sfx(last_played_footstep, footstep_delay); // Add delayed sfx to the sound manager

		// Message the level we've moved
		engine->level_manager->current_level->player_moved();
	}
}

void Player::resolve_item(Item & item, int move_direction_enum)
{
	// Is the item on the map?
	if (item.state == ItemState::ON_MAP) {
		if (current_item != nullptr) {
			current_item->state = ItemState::DISCARDED;
		}
		current_item = &item;

		// current_items is now picked up
		current_item->state = ItemState::PICKED_UP;
	}

	// Play item pickup sfx
	switch (item.type) {
	case ItemType::WEAPON:
		engine->sound_manager->get_sfx("sword_pickup")->sf_sound.play();
		break;
	}

	// Set the player to be in transit!
	player_state = PlayerStates::IN_TRANSIT;
	move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

	core::Vector2i dir = move_directions[move_direction_enum];
	tile_position += dir;
	world_position = ((core::Vector2f)tile_position * TILE_SIZE) + PLAYER_OFFSET;

	// Walk SFX
	last_played_footstep = get_random_footstep(2);
	engine->sound_manager->add_delayed_sfx(last_played_footstep, footstep_delay); // Add delayed sfx to the sound manager

	// Message the level we've moved
	engine->level_manager->current_level->player_moved();
}

void Player::reset_after_death()
{
	engine->level_manager->reInitCurrentLevel(); // Reset current level
	hp = 5; // Reset hp
	current_item = nullptr;

	// Disable the post processing effect
	engine->graphics_manager->set_post_processing_effect(POST_PROCESSING_EFFECTS::NONE);
	death_panel.offset = 0;
	//graphics::Shader* fbShader = ResourceManager::Instance()->GetShader("framebuffer_shader");
	//fbShader->enable();
	//fbShader->setUniformFloat("offset", 0);
	//fbShader->disable();
}

void Player::handle_item_use()
{
	if (current_item == nullptr)
		return void();

	// Continue and use current item!
	switch (current_item->type) {
	case ItemType::HEALTH:
		hp += current_item->value;
		if (hp >= 5)
			hp -= (5 - hp);
		current_item->state = ItemState::DISCARDED;
		current_item = nullptr;

		// Play sfx
		engine->sound_manager->get_sfx("eating_health_up")->sf_sound.play(); 

		break;
	case ItemType::WEAPON:
		printf("tried to use weapon\n");
		current_item = nullptr;
		break;
	case ItemType::SHIELD:
		printf("tried to use shield\n");
		current_item = nullptr;
		break;
	case ItemType::KEY:
		printf("tried to use key\n");
		current_item = nullptr;
		break;
	}
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}