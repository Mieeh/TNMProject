#include"include/gas.h"

#include"include/constants.h"
#include"../engine/include/game_systems.h"
#include"include/player.h"

#define BIG_SQUARE 1080.0f

using namespace bear;

Gas::Gas()
{
	current_x = 0;

	// Get the engine
	engine = Engine::Instance();

	// Setup the entities
	rect_entity.renderable.m_Transform.m_Size = { BIG_SQUARE, BIG_SQUARE };
	rect_entity.renderable.m_Color = core::Color::Black();
	rect_entity.renderable.m_Layer = 9999;
	
	gas_entity.renderable.m_Transform.m_Size = { TILE_SIZE, BIG_SQUARE };
	gas_entity.renderable.m_TextureName = "shadows";
	gas_entity.renderable.m_Layer = 9999; // This is rendered on top of everything

	gas_speed = GAS_MOVE_SPEED;
}

void Gas::reset_gas_to_current_level()
{
	// Get the level specifik values
	current_x = engine->level_manager->current_level->gas_offset;
	step_interval = engine->level_manager->current_level->gas_interval;
	step_counter = 0;
								  
	// Set the gas position to these new values
	gas_entity.renderable.m_Transform.m_Position.x =  (current_x * TILE_SIZE);
	rect_entity.renderable.m_Transform.m_Position.x = (current_x * TILE_SIZE) - BIG_SQUARE;
}

void Gas::draw()
{
	// Draw the gás 
	engine->graphics_manager->draw(rect_entity);
	engine->graphics_manager->draw(gas_entity);
}

void Gas::update(float dt)
{
	float goal_pos = (current_x * TILE_SIZE);
	if (gas_entity.renderable.m_Transform.m_Position.x <= goal_pos) {
		gas_entity.renderable.m_Transform.m_Position.x += gas_speed * dt;
	}
	if (rect_entity.renderable.m_Transform.m_Position.x < goal_pos - BIG_SQUARE + 10) {
		rect_entity.renderable.m_Transform.m_Position.x += gas_speed * dt;
	}
}

void Gas::reset_gas_speed()
{
	gas_speed = GAS_MOVE_SPEED;
}

void Gas::player_event()
{
	step_counter++;
	if (step_interval > 0) {
		if (step_counter >= step_interval) {
			step_counter = 0;
			current_x++;
		}
	}
}