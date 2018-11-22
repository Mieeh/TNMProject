#pragma once

#include"../../engine/include/entity.h"

struct Gas {

	Entity gas_entity; // The gas entity with the gas sprite
	Entity rect_entity; // The big black rectangle behind the gas entity
	int current_x;
	int step_interval; // Move the gas forward each step_interval 
	int step_counter; // Counter for when the gas will move forward again
	
	void player_moved();

	void draw();
};