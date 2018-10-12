#include"include\player.h"

#include"include/constants.h"

#include"../engine/include/game_systems.h"
#include"../engine/include/enemy.h"

#include<window/event.h>
#include<window/GLFW_event.h>
using namespace bear;

Player* Player::instance = nullptr;

Player::Player()
{
	entity.renderable.m_Color = core::Color::Red();
	entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
}

void Player::on_event(Event & event)
{
	if (event.type == EventType::KeyPressed) {
		// Make sure the player is idle before we move/perform something!
		if (player_state == PlayerStates::IDLE) {
			if (event.key == Key::D)
				move_player(PlayerMoveDirection::RIGHT);
			else if (event.key == Key::A)
				move_player(PlayerMoveDirection::LEFT);
			else if (event.key == Key::S)
				move_player(PlayerMoveDirection::DOWN);
			else if (event.key == Key::W)
				move_player(PlayerMoveDirection::UP);
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
			entity.renderable.m_Transform.m_Position.y += move_speed*0.25f*dt;
			entity.renderable.m_Color.a += 0.0015f*dt;
		}
		else {
			player_state = PlayerStates::IDLE;
			entity.renderable.m_Transform.m_Position = world_position;
			entity.renderable.m_Color.a = 1.0f;
		}
		break;
	}
}		

void Player::render()
{
	GraphicsSingleton::Instance()->draw(entity);
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

		std::cout << (std::string)tile_position << std::endl;
	}
	else if (is_enemy(new_tile_value)) {
		std::string k = (std::string)new_tile_position;
		std::cout << LevelManagerSingleton::Instance()->current_level->get_level_content().enemies.at(k).hp << std::endl;
		LevelManagerSingleton::Instance()->current_level->get_level_content().enemies.at(k).hp -= 10;
	}
}

void Player::set_player_position(const core::Vector2i position)
{
	// Sets the player position (instantly no state logic)
	tile_position = position;
	world_position = (core::Vector2f)tile_position * TILE_SIZE;
	entity.renderable.m_Transform.m_Position = world_position;
}

void Player::move_player_state_control(PlayerMoveDirection dir, float dt)
{
	switch (dir) {
	case PlayerMoveDirection::RIGHT:
		// Move towards the goal position
		entity.renderable.m_Transform.m_Position.x += move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position!
		if (entity.renderable.m_Transform.m_Position.x >= world_position.x) {
			player_state = PlayerStates::IDLE;
			entity.renderable.m_Transform.m_Position = world_position;
		}
		break;
	case PlayerMoveDirection::LEFT:
		entity.renderable.m_Transform.m_Position.x += -move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position!
		if (entity.renderable.m_Transform.m_Position.x <= world_position.x) {
			player_state = PlayerStates::IDLE;
			entity.renderable.m_Transform.m_Position = world_position;
		}
		break;
	case PlayerMoveDirection::DOWN:
		entity.renderable.m_Transform.m_Position.y += move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position
		if (entity.renderable.m_Transform.m_Position.y >= world_position.y) {
			player_state = PlayerStates::IDLE;
			entity.renderable.m_Transform.m_Position = world_position;
		}
		break;
	case PlayerMoveDirection::UP:
		entity.renderable.m_Transform.m_Position.y += -move_speed * dt;
		// Make sure we go to an idle state when we've reached our new position
		if (entity.renderable.m_Transform.m_Position.y <= world_position.y) {
			player_state = PlayerStates::IDLE;
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
	static const int intro_offset = -100;
	entity.renderable.m_Transform.m_Position = world_position + core::Vector2f(0, intro_offset);

	entity.renderable.m_Color.a = 0.0f;
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}