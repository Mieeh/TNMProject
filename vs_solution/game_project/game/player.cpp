#include"include\player.h"

#include"include/constants.h"
#include"include/combat.h"

#include"../engine/include/bear_game.h"
#include"../engine/include/game_systems.h"
#include"../engine/include/enemy.h"

#include<window/event.h>
#include<window/GLFW_event.h>
using namespace bear;

Player* Player::instance = nullptr;

Player::Player()
{
	entity.renderable.m_TextureName = "runningDown3";
	entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
	entity.renderable.m_Layer = LAYER3;
}

void Player::on_event(Event & event)
{					
	if (event.type == EventType::KeyPressed) {
		// Make sure the player is idle before we move/perform something!
		if (player_state == PlayerStates::IDLE) {
			if (event.key == config_singleton->key_map.at("MOVE_RIGHT"))
				move_player(PlayerMoveDirection::RIGHT);
			else if (event.key == config_singleton->key_map.at("MOVE_LEFT"))
				move_player(PlayerMoveDirection::LEFT);
			else if (event.key == config_singleton->key_map.at("MOVE_DOWN"))
				move_player(PlayerMoveDirection::DOWN);
			else if (event.key == config_singleton->key_map.at("MOVE_UP"))
				move_player(PlayerMoveDirection::UP);
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
	// What're we doing?
	switch (player_state) {
	case PlayerStates::IDLE:
		idle_player_state_control();
		break;
	case PlayerStates::IN_TRANSIT:
		move_player_state_control(move_direction, dt);
		break;
	case PlayerStates::INTRO:
		// Do intro logic
		if (entity.renderable.m_Transform.m_Position.y < world_position.y) {
			//core::lerp(entity.renderable.m_Transform.m_Position.y, world_position.y, 0.001f*dt);
			entity.renderable.m_Transform.m_Position.y += fall_speed * dt;
			entity.renderable.m_Color.a += 0.0015f*dt;
		}
		else {
			player_state = PlayerStates::IDLE;
			entity.renderable.m_Transform.m_Position = world_position;
			entity.renderable.m_Color.a = 1.0f;
			Engine::instance->perform_window_shake(400, 10); 
		}
		break;
	case PlayerStates::OUTRO:
		
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
			level_manager_singleton->setCurrentLevel(level_manager_singleton->current_level->next_level_name); // Load the next level
			// Reset layer
			entity.renderable.m_Layer = LAYER3;
		}
		
		break;

	case PlayerStates::DEAD:
		death_panel.fade_to_1(dt);
		break;
	}
}		

void Player::render()
{
	GraphicsSingleton::Instance()->draw(entity);
	// Dead? render the death panel if we are!
	if (player_state == PlayerStates::DEAD) {
		death_panel.entity.renderable.m_Transform.m_Size = GraphicsSingleton::Instance()->window_size;
		GraphicsSingleton::Instance()->draw_as_ui(death_panel.entity);
	}
}

void Player::move_player(int move_direction_enum)
{
	core::Vector2i new_tile_position = tile_position + move_directions[move_direction_enum];
	int new_tile_value = LevelManagerSingleton::Instance()->current_level->get_level_content().tile_map.at(new_tile_position.y).at(new_tile_position.x);

	// We trying to transit to a floor?
	if (is_floor(new_tile_value)) {
		// Set the player to be in transit!
		player_state = PlayerStates::IN_TRANSIT;
		move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

		core::Vector2i dir = move_directions[move_direction_enum];
		tile_position += dir;
		world_position = (core::Vector2f)tile_position * TILE_SIZE;

		// Message the level we've moved
		LevelManagerSingleton::Instance()->current_level->player_moved();
	}
	else if (is_enemy(new_tile_value)) {
		// Get the enemy!
		std::string key = (std::string)new_tile_position;
		EnemyBase& enemy = level_manager_singleton->current_level->get_level_content().enemies.at(key);
		resolve_combat(enemy, move_direction_enum);
	}
	else if (new_tile_value == GOAL) {

		goal_trigger = true;

		// Set the player to be in transit!
		player_state = PlayerStates::IN_TRANSIT;
		move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

		core::Vector2i dir = move_directions[move_direction_enum];
		tile_position += dir;
		world_position = (core::Vector2f)tile_position * TILE_SIZE;
	}

	// Update the layer
	entity.renderable.m_Layer = LAYER3 + tile_position.y;
}

void Player::set_player_position(const core::Vector2i position)
{
	// Sets the player position (instantly no state logic)
	tile_position = position;
	world_position = (core::Vector2f)tile_position * TILE_SIZE;
	entity.renderable.m_Transform.m_Position = world_position;
}

void Player::set_player_state(PlayerStates new_state)
{
	player_state = new_state;
	if (goal_trigger) {
		player_state = PlayerStates::OUTRO;
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
	world_position = (core::Vector2f)tile_position * TILE_SIZE;
	static const int intro_offset = -350; 
	entity.renderable.m_Transform.m_Position = world_position + core::Vector2f(0, intro_offset);

	entity.renderable.m_Color.a = 0.0f;
}

void Player::resolve_combat(EnemyBase& enemy, int move_direction_enum)
{
	// Check to make sure the enemy isn't already dead!
	if (!enemy.is_dead) {
		// Perform combat with the enemy
		CombatResult combat_result = Combat::perform_combat(enemy);

		// What happend during the combat? 
		switch (combat_result) {
		case CombatResult::ENEMY_DIED:
			enemy.is_dead = true;
			break;
		case CombatResult::PLAYER_DIED:
			set_player_state(PlayerStates::DEAD);
			death_panel.a = 0.0f;
			break;
		case CombatResult::CLASH:
			break;
		}
	}
	else {
		// Set the player to be in transit!
		player_state = PlayerStates::IN_TRANSIT;
		move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

		core::Vector2i dir = move_directions[move_direction_enum];
		tile_position += dir;
		world_position = (core::Vector2f)tile_position * TILE_SIZE;

		// Message the level we've moved
		LevelManagerSingleton::Instance()->current_level->player_moved();
	}
}

void Player::reset_after_death()
{
	level_manager_singleton->reInitCurrentLevel(); // Reset current level
	hp = 5; // Reset hp
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}