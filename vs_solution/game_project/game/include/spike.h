#pragma once

#include"../../engine/include/entity.h"

#define SPIKE_DOWN 0
#define SPIKE_ALMOST_UP 1
#define SPIKE_FULLY_UP 2

struct Spike {

	// Members
	Entity entity;
	unsigned short int current_level;

	// Change over to the correct sprite
	void update(float dt);

	// Level goes from 0 to 4
	// 0 - harmless completely down
	// 1 - harmless completely down
	// 2 - cant walk onto it without dying
	// 3 - cant walk onto it without dying
	// 4 - insta death
	//
	// So there's basically 3 spike states, being:
	// 1. Harmless
	// 2. Deadly if you walk onto it, standing on it is okay
	// 3. Insta death
	void update_spike_level(unsigned short int level);

};