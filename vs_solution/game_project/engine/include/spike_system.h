#pragma once

#include<vector>

#include"../../engine/include/entity.h"

#include<graphics/animated_sprite.h>

struct Engine;

struct SpikeSystem {

	/*
	0 - no harm (spike0.png)
	1 - no harm (spike0.png)
	2 - some harm (spike1.png)
	3 - deadly (spike4.png)
	*/
	unsigned int current_spike_level = 0;
	bear::graphics::AnimatedSprite spike_go_up, spike_go_down;
	// List, unique for each level
	std::vector<Entity> spike_entity_list;
	Engine *engine;
	std::string texture_name;

	SpikeSystem();

	void reset_spikes();
	void incement_spike_level();
	void update(float dt);
	void render();
};