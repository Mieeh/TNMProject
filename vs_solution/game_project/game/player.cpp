#include"include\player.h"

#include"include/constants.h"

#include"../engine/include/game_systems.h"

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
	entity.renderable.m_Transform.m_Position = (core::Vector2f)world_position;	
}

void Player::render()
{
	GraphicsSingleton::Instance()->draw(entity);
}

void Player::player_move(const core::Vector2i & walk_direction)
{
	tile_position += walk_direction;
	world_position = tile_position * TILE_SIZE;
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}