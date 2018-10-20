#pragma once

#include"../../engine/include/entity.h"

struct DeathPanel {

	DeathPanel();

	Entity entity;
	float a;
	float fade_speed;

	void fade_to_1(float dt);
	void fade_to_0(float dt);
};