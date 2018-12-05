#pragma once

#include<core\vector2.h>
#include"entity.h"

using namespace bear;

struct EnemyBase {
	// Graphical representation
	Entity entity;
	
	// Gameplay related
	std::string name;
	int hp;
	int damage;
	bool is_dead = false;	
};