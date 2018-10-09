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
	entity.renderable.m_Transform.m_Position.moveTowards(core::Vector2f(position.x, position.y)*TILE_SIZE, 10.0f*dt);
	
	//static core::Vector2i v1(1, 1);
	//static core::Vector2i v2(100, 100);
	//core::moveTowards2i(v1, v2, 1.5f*dt);
	//std::cout << v1 << std::endl;

	//core::Vector2i integerPosition = core::Vector2i((int)entity.renderable.m_Transform.m_Position.x, (int)entity.renderable.m_Transform.m_Position.y);
	//std::cout << "Entity position: " << integerPosition << std::endl;
	//std::cout << "Position: " << position*TILE_SIZE << std::endl;
	//if (integerPosition.x == position.x*TILE_SIZE && integerPosition.y == position.y*TILE_SIZE) {
	//	std::cout << "on the tile!" << std::endl;
	//}
}

void Player::render()
{
	GraphicsSingleton::Instance()->draw(entity);
}

void Player::player_move(const core::Vector2i & walk_direction)
{
	core::Vector2i newPos = position + walk_direction;
	position = newPos;
	
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}