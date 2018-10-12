#pragma once

#include"../../../engine/include/enemy.h"

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