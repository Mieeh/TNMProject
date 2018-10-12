#pragma once

#include<core\vector2.h>
#include"entity.h"

using namespace bear;

struct EnemyBase {
	// Graphical representation
	Entity entity;
	core::Vector2i tile_position;

	// Gameplay related
	std::string name;
	int hp;
	int damage;
};