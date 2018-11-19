#pragma once

#include"../../../engine/include/enemy.h"

#define BAT_SIZE_X 1
#define BAT_SIZE_Y 1.5f
#define BAT_OFFSET_X 0
#define BAT_OFFSET_Y -40

struct Bat : EnemyBase {

	// Constructor
	Bat() 
	{
		// Setup the enemy
		hp = 2;
		damage = 1;
		name = "Bat";
		entity.renderable.m_TextureName = "test_enemy";
	}
};