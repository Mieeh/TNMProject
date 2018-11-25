#pragma once

#include"../../engine/include/entity.h"
#include"../../engine/include/bear_game.h"

struct Gas {

	Entity gas_entity; // The gas entity with the gas sprite
	Entity rect_entity; // The big black rectangle behind the gas entity
	int current_x;
	int step_interval; // Move the gas forward each step_interval 
	int step_counter; // Counter for when the gas will move forward again
	Engine* engine;
	
	/* Constructor & Methods */
	Gas();

	void reset_gas_to_current_level();

	void player_event();
	void draw();
	void update(float dt); 
};