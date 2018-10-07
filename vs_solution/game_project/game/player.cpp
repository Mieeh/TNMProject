#include"include\player.h"

#include"include/constants.h"

#include"../engine/include/game_systems.h"

Player* Player::instance = nullptr;

Player::Player()
{
	entity.renderable.m_Color = core::Color::Red();
	entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
}

void Player::on_event(Event & event)
{
}

void Player::update(float dt)
{
}

void Player::render()
{
	entity.renderable.m_Transform.m_Position = core::Vector2f(position.x, position.y)*TILE_SIZE;
	GraphicsSingleton::Instance()->draw(entity);
}

Player* Player::get()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}