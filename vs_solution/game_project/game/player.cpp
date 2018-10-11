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
		if (event.key == Key::D)
			move_right();
		else if (event.key == Key::A)
			move_left();
		else if (event.key == Key::S)
			move_down();
		else if (event.key == Key::W)
			move_up();
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
			std::cout << "move to the right" << std::endl;
			// Move to the right!			
			break;
		case PlayerMoveDirection::LEFT: 
			std::cout << "move to the left" << std::endl;
			// Move to the left
			break;
		case PlayerMoveDirection::DOWN: 
			std::cout << "move down" << std::endl;
			// Move down
			break;
		case PlayerMoveDirection::UP: 
			std::cout << "move up" << std::endl;
			// Move up
			break;
		}
		break;
	}
}		

void Player::render()
{
	GraphicsSingleton::Instance()->draw(entity);
}

void Player::move_player(const core::Vector2i direction)
{
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}