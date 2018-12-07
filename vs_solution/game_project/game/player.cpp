#include"include\player.h"

#include"include/constants.h"
#include"include/combat.h"

#include"../engine/include/bear_game.h"
#include"../engine/include/game_systems.h"
#include"../engine/include/enemy.h"

#include<window/event.h>
#include<window/GLFW_event.h>
#include<graphics\graphics.h>
using namespace bear;

#include<random>

#define SHIELD_HOLD_OFFSET core::Vector2f(0, -37)
#define WEAPON_HOLD_OFFSET core::Vector2f(0, -25)
#define HEALTH_HOLD_OFFSET core::Vector2f(0, -30)
#define KEY_HOLD_OFFSET core::Vector2f(0, -22)

Player* Player::instance = nullptr;

Player::Player() : player_anim(), player_ui(), gas(), do_key_fly(false)
{
	entity.renderable.m_TextureName = "runningDown3";
	entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE)*PLAYER_SIZE;
	entity.renderable.m_Layer = LAYER3;
	player_offset = DEFAULT_PLAYER_OFFSET;
	show_item = true;
	standing_on_spike = false;
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
	if (event.type == EventType::KeyPressed && !move_lock) {
		// Make sure the player is idle before we move/perform something!
		if (player_state == PlayerStates::IDLE) {
			if (event.key == engine->config_manager->key_map.at("MOVE_RIGHT"))
				resolve_move(PlayerMoveDirection::RIGHT);
			else if (event.key == engine->config_manager->key_map.at("MOVE_LEFT"))
				resolve_move(PlayerMoveDirection::LEFT);
			else if (event.key == engine->config_manager->key_map.at("MOVE_DOWN"))
				resolve_move(PlayerMoveDirection::DOWN);
			else if (event.key == engine->config_manager->key_map.at("MOVE_UP"))
				resolve_move(PlayerMoveDirection::UP);

			if (event.key == engine->config_manager->key_map.at("INTERACT2")) { // 'e' by default
				handle_item_use();
			}
			if (event.key == engine->config_manager->key_map.at("INTERACT1")) {
				engine->level_manager->reInitCurrentLevel();
				reset_after_death();
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
	// Update the gas
	gas.update(dt);

	// Update the animation object
	entity.renderable.m_TextureName = player_anim.update(player_state, move_direction, dt);

	// What're we doing?
	switch (player_state) {
	case PlayerStates::IDLE:
		idle_player_state_control();
		break;
	case PlayerStates::IN_TRANSIT:
		// Returns true when the player reaches its destianation
		if (move_player_state_control(move_direction, dt)) {
			set_player_state(PlayerStates::IDLE);
			if (die_trigger) {
				die_trigger = false;
				set_player_state(PlayerStates::DEAD);
			}
		}
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

	if (do_key_fly) {
		key_fly.renderable.m_Layer = entity.renderable.m_Layer + 1;
		key_fly.renderable.m_Transform.m_Position.moveTowards(key_fly_target, key_fly_speed*25*dt);
		key_fly.renderable.m_Color.a -= key_fly_speed * 0.1f * dt;
		if (key_fly.renderable.m_Color.a <= 0) {
			// We're done!
			do_key_fly = false;
		}
	}
}		

void Player::render()
{
	// Draw player related UI
	player_ui.render_player_hp();

	// render holding item (if we want to)
	if (current_item != nullptr && show_item) {
		switch (current_item->type) {
		case ItemType::SHIELD:
			holding_item.renderable.m_Transform.m_Position = entity.renderable.m_Transform.m_Position + SHIELD_HOLD_OFFSET;
			holding_item.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
			holding_item.renderable.m_TextureName = "shield";
			break;
		case ItemType::HEALTH:
			holding_item.renderable.m_Transform.m_Position = entity.renderable.m_Transform.m_Position + HEALTH_HOLD_OFFSET;
			holding_item.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
			holding_item.renderable.m_TextureName = "food";
			break;
		case ItemType::KEY:
			holding_item.renderable.m_Transform.m_Position = entity.renderable.m_Transform.m_Position + KEY_HOLD_OFFSET;
			holding_item.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
			holding_item.renderable.m_TextureName = (current_item->name == "KeyRed") ? "key_red" : "key";
			break;
		case ItemType::WEAPON:
			holding_item.renderable.m_Transform.m_Position = entity.renderable.m_Transform.m_Position + WEAPON_HOLD_OFFSET;
			holding_item.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
			holding_item.renderable.m_TextureName = "sword";
			break;
		}

		holding_item.renderable.m_Layer = entity.renderable.m_Layer+1;
		engine->graphics_manager->draw(holding_item);
	}

	// Draw the player entity
	engine->graphics_manager->draw(entity);

	// Draw the gas entity(*)
	gas.draw();

	if (do_key_fly) {
		engine->graphics_manager->draw(key_fly);
	}
}

void Player::resolve_move(int move_direction_enum)
{
	core::Vector2i new_tile_position = tile_position + move_directions[move_direction_enum];
	int new_tile_value = engine->level_manager->current_level->get_level_content().tile_map.at(new_tile_position.y).at(new_tile_position.x);

	// Make sure we disable the presure plate (if we stood on one)
	if (presure_plate != nullptr) {
		presure_plate->toggle();
		engine->sound_manager->get_sfx("pp0")->sf_sound.play();
		presure_plate = nullptr;
	}

	// We trying to transit to a floor?
	if (is_floor(new_tile_value)) {
		do_move_player(move_direction_enum);
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
	else if (is_pp(new_tile_value)) {
		// Move the player to the presure plate
		do_move_player(move_direction_enum);
		
		// Get the presure plate
		std::string key = (std::string)new_tile_position;
		presure_plate = &engine->level_manager->current_level->get_level_content().presure_plates.at(key);
		presure_plate->toggle();

		// SFX
		engine->sound_manager->get_sfx("pp1")->sf_sound.play();
		//engine->sound_manager->add_delayed_sfx("pp1", 150);
	}
	else if (new_tile_value == GOAL) {

		goal_trigger = true;

		// Set the player to be in transit!
		player_state = PlayerStates::IN_TRANSIT;
		move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

		core::Vector2i dir = move_directions[move_direction_enum];
		tile_position += dir;
		world_position = ((core::Vector2f)tile_position * TILE_SIZE) + player_offset;
	}
	else if (new_tile_value == SPIKE) {
		standing_on_spike = true;

		// Should we die?
		std::cout << engine->level_manager->current_level->get_level_content().spike_system.current_spike_level << std::endl;
		if (engine->level_manager->current_level->get_level_content().spike_system.current_spike_level == 3) {
			set_player_state(PlayerStates::DEAD);
		}

		do_move_player(move_direction_enum);
	}
	else if (is_gate(new_tile_value)) {
		std::string key = (std::string)new_tile_position;
		Gate& gate = engine->level_manager->current_level->get_level_content().gates.at(key);

		// Is the gate up?
		if (gate.gate_state == GATE_STATE::LOCKED) {
			if (current_item != nullptr) {
				if (current_item->type == ItemType::KEY) {
					// Make sure the key color matches up!
					if ((gate.gate_type == GATE_TYPE::RED && current_item->name == "Key") || 
						(gate.gate_type == GATE_TYPE::NORMAL && current_item->name == "KeyRed")) {
						return;
					}
					current_item = nullptr;
					gate.unlock();
					// SFX
					engine->sound_manager->get_sfx("key_unlock")->sf_sound.play();
					engine->sound_manager->get_sfx("door_open")->sf_sound.play();
				}
			}
		}
		else {
			do_move_player(move_direction_enum);
		}
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

void Player::do_move_player(int move_direction_enum)
{
	if (player_state == PlayerStates::DEAD) {
		return void();
	}
	// Set the player to be in transit!
	player_state = PlayerStates::IN_TRANSIT;
	move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

	core::Vector2i dir = move_directions[move_direction_enum];
	tile_position += dir;
	world_position = ((core::Vector2f)tile_position * TILE_SIZE) + player_offset;

	// Check spike stance
	int standing_tile_value = engine->level_manager->current_level->get_level_content().tile_map.at(tile_position.y).at(tile_position.x);
	if (standing_tile_value != SPIKE)
		standing_on_spike = false;

	// Walk SFX
	last_played_footstep = get_random_footstep(2);

	engine->sound_manager->add_delayed_sfx(last_played_footstep, footstep_delay); // Add delayed sfx to the sound manager

	// Make sure the attack animation isnt playing
	player_anim.stop_attack();

	// Message the level we've moved & the gas we've done a gas related action
	engine->level_manager->current_level->player_moved();
	message_gas();
}

void Player::set_player_position(const core::Vector2i position)
{
	// Sets the player position (instantly no state logic)
	tile_position = position;
	world_position = ((core::Vector2f)tile_position * TILE_SIZE) + player_offset;
	entity.renderable.m_Transform.m_Position = world_position;
}

void Player::set_player_state(PlayerStates new_state)
{
	player_state = new_state;
	if (goal_trigger) {
		engine->sound_manager->get_sfx("falling")->sf_sound.play();
		player_state = PlayerStates::OUTRO;
	}

	if (new_state == PlayerStates::DEAD) {
		// Tell the graphics_manager we want to enable the death post processing effect
		engine->graphics_manager->set_post_processing_effect(POST_PROCESSING_EFFECTS::BLACK_WHITE_CROSS);
		// Play the death chords 
		engine->sound_manager->set_background_music("game_over_music"); 
		// SFX
		engine->sound_manager->get_sfx("player_die")->sf_sound.play();
		// Animation
		player_anim.stop_death();
		player_anim.play_death();
		// Remove item
		current_item = nullptr;
	}
}

bool Player::move_player_state_control(PlayerMoveDirection dir, float dt)
{
	switch (dir) {
	case PlayerMoveDirection::RIGHT:
		// Move towards the goal position
		entity.renderable.m_Transform.m_Position.x += move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position!
		if (entity.renderable.m_Transform.m_Position.x >= world_position.x) {
			entity.renderable.m_Transform.m_Position = world_position;
			//set_player_state(PlayerStates::IDLE);
			return true;
		}
		break;
	case PlayerMoveDirection::LEFT:
		entity.renderable.m_Transform.m_Position.x += -move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position!
		if (entity.renderable.m_Transform.m_Position.x <= world_position.x) {
			entity.renderable.m_Transform.m_Position = world_position;
			//set_player_state(PlayerStates::IDLE);
			return true;
		}
		break;
	case PlayerMoveDirection::DOWN:
		entity.renderable.m_Transform.m_Position.y += move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position
		if (entity.renderable.m_Transform.m_Position.y >= world_position.y) {
			entity.renderable.m_Transform.m_Position = world_position;
			//set_player_state(PlayerStates::IDLE);
			return true;
		}
		break;
	case PlayerMoveDirection::UP:
		entity.renderable.m_Transform.m_Position.y += -move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position
		if (entity.renderable.m_Transform.m_Position.y <= world_position.y) {
			entity.renderable.m_Transform.m_Position = world_position;
			//set_player_state(PlayerStates::IDLE);
			return true;
		}
		break;
	}

	return false;
}

void Player::idle_player_state_control()
{
	// Do idle stuff
}

void Player::play_intro_at(const core::Vector2i position)
{
	player_state = PlayerStates::INTRO;
	tile_position = position;
	world_position = ((core::Vector2f)tile_position * TILE_SIZE) + player_offset;
	static const int intro_offset = -350; 
	entity.renderable.m_Transform.m_Position = world_position + core::Vector2f(0, intro_offset);

	entity.renderable.m_Color.a = 0.0f;

	// reset the gas
	gas.reset_gas_to_current_level();

	// Reset player HP
	hp = 3;
	current_item = nullptr;
}

void Player::resolve_combat(EnemyBase& enemy, int move_direction_enum)
{
	// Check to make sure the enemy isn't already dead!
	if (!enemy.is_dead) {
		// Perform combat with the enemy
		CombatResult combat_result = Combat::perform_combat(&enemy);

		// What happend during the combat? 
		switch (combat_result) {
		case CombatResult::ENEMY_DIED:
			// Animation
			player_anim.play_attack(move_direction_enum);
			enemy.is_dead = true;
			// Notes(david) if the enemy we just killed is not a "bones" enemy then this would be weird?
			engine->sound_manager->get_sfx("enemy_dead_bones")->sf_sound.play();
			//engine->perform_window_shake(160, 4);
			engine->graphics_manager->perform_view_shake(200, 5);
			break;
		case CombatResult::PLAYER_DIED:
			set_player_state(PlayerStates::DEAD);
			break;
		case CombatResult::CLASH:
			// Animation
			player_anim.play_attack(move_direction_enum);
			// Window shake
			//engine->perform_window_shake(100, 3);
			engine->graphics_manager->perform_view_shake(200, 5);
			// Enemy hurt sfx
			engine->sound_manager->get_sfx("enemy_hurt")->sf_sound.play();
			break;
		}

		// Gas
		message_gas();
	}
	else {
		// Set the player to be in transit!
		do_move_player(move_direction_enum);
	}
}

void Player::resolve_item(Item & item, int move_direction_enum)
{
	// Is the item on the map?
	if (item.state == ItemState::ON_MAP) {
		// Discard current item if there is anys
		if (current_item != nullptr) {
			// Discard current item unless it's a key!
			current_item->state = ItemState::DISCARDED;
			if (current_item->type == ItemType::KEY) {
				// Setup key fly
				key_fly.renderable.m_Transform.m_Position = entity.renderable.m_Transform.m_Position + KEY_HOLD_OFFSET;
				key_fly.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
				key_fly.renderable.m_TextureName = (current_item->name == "KeyRed") ? "key_red" : "key";
				key_fly.renderable.m_Color.a = 1.0f;
				do_key_fly = true;
				key_fly_target = current_item->entity.renderable.m_Transform.m_Position;
				// Make sure the key is still on the map afterwards!
				current_item->state = ItemState::ON_MAP;
			}
		}
		current_item = &item;

		// current_items is now picked up
		current_item->state = ItemState::PICKED_UP;
		
		// Play item pickup sfx
		switch (item.type) {
		case ItemType::WEAPON:
			engine->sound_manager->get_sfx("sword_pickup")->sf_sound.play();
			break;
		case ItemType::SHIELD:
			engine->sound_manager->get_sfx("armor_pickup")->sf_sound.play();
			break;
		case ItemType::KEY:
			engine->sound_manager->get_sfx("key_pickup")->sf_sound.play();
			break;
		case ItemType::HEALTH:
			engine->sound_manager->get_sfx("food_pickup")->sf_sound.play();
			break;
		}
	}

	// Set the player to be in transit!
	do_move_player(move_direction_enum);
}

void Player::reset_after_death()
{
	engine->level_manager->reInitCurrentLevel(); // Reset current level
	engine->level_manager->current_level->get_level_content().spike_system.reset_spikes();
	hp = 3; // Reset hp

	// Disable the post processing effect
	engine->graphics_manager->set_post_processing_effect(POST_PROCESSING_EFFECTS::NONE);
	death_panel.offset = 0;
}

void Player::handle_item_use()
{
	if (current_item == nullptr)
		return void();

	// Continue and use current item!
	switch (current_item->type) {
	case ItemType::HEALTH:
		if (hp < 3) {
			hp += current_item->value;
			current_item->state = ItemState::DISCARDED;
			current_item = nullptr;

			// Play sfx
			engine->sound_manager->get_sfx("eating_health_up")->sf_sound.play();

			message_gas();
		}

		break;
	case ItemType::WEAPON:
		break;
	case ItemType::SHIELD:
		break;
	case ItemType::KEY:
		break;
	}
}

void Player::message_gas()
{
	gas.player_event();
	// Check if we're inside the gas!
	if (gas.current_x >= tile_position.x) {
		set_player_state(PlayerStates::DEAD);
	}
	
	// Also message the spikes here?
	if (!die_trigger) {
		engine->level_manager->current_level->get_level_content().spike_system.incement_spike_level();
	}

	if (standing_on_spike && engine->level_manager->current_level->get_level_content().spike_system.current_spike_level == 3) {
		set_player_state(PlayerStates::DEAD);
	}

	// Find the closest spike
	// x=player and y=spike
	// abs(player.x−spike.x) + abs(player.y−spike.y)
	bool play_spike_sfx = false;
	const int distance_to_sfx = 1;

	for (const auto&spike : engine->level_manager->current_level->get_level_content().spike_tile_list) {
		int distance = std::abs(tile_position.x - spike.x) + std::abs(tile_position.y - spike.y);
		if (distance <= distance_to_sfx) {
			play_spike_sfx = true;
			break;
		}
	}

	if (play_spike_sfx) {
		if (engine->level_manager->current_level->get_level_content().spike_system.current_spike_level == 3) {
			engine->sound_manager->get_sfx("spike_up")->sf_sound.play();
		}
		else if (engine->level_manager->current_level->get_level_content().spike_system.current_spike_level == 0) {
			engine->sound_manager->get_sfx("spike_down")->sf_sound.play();
		}
	}
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}