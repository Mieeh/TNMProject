#include"include\player.h"

#include"include/constants.h"

#include"../engine/include/game_systems.h"

#include<window/event.h>
#include<window/GLFW_event.h>
using namespace bear;

#include<cmath>

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
	switch (player_state) {
	case PlayerStates::IDLE:
		// Do idle stuff
		std::cout << "I am idle" << std::endl;
		break;
	case PlayerStates::IN_TRANSIT:
		switch (move_direction) {
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
		break;
	}
}		

void Player::render()
{
	GraphicsSingleton::Instance()->draw(entity);
}

void Player::move_player(int move_direction_enum)
{
	// Set the player to be in transit!
	player_state = PlayerStates::IN_TRANSIT;
	move_direction = static_cast<PlayerMoveDirection>(move_direction_enum);

	core::Vector2i dir = move_directions[move_direction_enum];
	tile_position += dir;
	world_position = (core::Vector2f)tile_position * TILE_SIZE;
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}