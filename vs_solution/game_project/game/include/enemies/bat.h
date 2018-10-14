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
		hp = 3;
		damage = 1;
		name = "Bat";
		entity.renderable.m_TextureName = "bat";

		// Whoever or whatever instantiated the bat should place it and handle all that we only setup the gameplay stat + texture name and nothing else
	}
};