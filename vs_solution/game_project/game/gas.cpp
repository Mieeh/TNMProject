#include"include/gas.h"

#include"include/constants.h"

#define BIG_SQUARE 700.0f

using namespace bear;

Gas::Gas()
{
	current_x = 0;

	// Get the engine
	engine = Engine::Instance();

	// Setup the entities
	rect_entity.renderable.m_Transform.m_Size = { BIG_SQUARE, BIG_SQUARE };
	rect_entity.renderable.m_Color = core::Color::Black();
	
	gas_entity.renderable.m_Transform.m_Size = { TILE_SIZE, BIG_SQUARE };
	gas_entity.renderable.m_Color = core::Color::Black();
	gas_entity.renderable.m_Layer = 999;
}

void Gas::draw()
{
	gas_entity.renderable.m_Transform.m_Position.x = current_x * TILE_SIZE;

	// Draw the gás 
	//engine->graphics_manager->draw(rect_entity);
	engine->graphics_manager->draw(gas_entity);
}

void Gas::player_moved()
{
	current_x++;
}