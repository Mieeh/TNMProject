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
			player_move({ 1, 0 });
		else if (event.key == Key::A)
			player_move({ -1, 0 });
		else if (event.key == Key::S)
			player_move({ 0, 1 });
		else if (event.key == Key::W)
			player_move({ 0, -1 });
	}
}

void Player::update(float dt)
{	
	//core::Vector2f current_world_pos = entity.renderable.m_Transform.m_Position;	
	
	//float a = 0.1f;
	//float b = 0.2f;

	// Move towards target position
#define EPSILON 0.8f
	float delta = std::fabs((entity.renderable.m_Transform.m_Position.x - world_position.x));
	if (delta < EPSILON) {
		std::cout << "on tile ";
	}
	entity.renderable.m_Transform.m_Position.moveTowards(world_position, move_speed*dt);
}		

void Player::render()
{
	GraphicsSingleton::Instance()->draw(entity);
}

void Player::set_position(const core::Vector2i & new_position)
{
	tile_position = new_position;
	world_position = (core::Vector2f)tile_position*TILE_SIZE;
}

void Player::player_move(const core::Vector2i & walk_direction)
{
	tile_position += walk_direction;
	world_position = (core::Vector2f)tile_position * TILE_SIZE;
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}