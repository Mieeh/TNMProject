#pragma once

#include"../../../engine/include/enemy.h"

#define SKELETON_SIZE_X 1.3
#define SKELETON_SIZE_Y 1.3
#define SKELETON_OFFSET_X -8.6
#define SKELETON_OFFSET_Y -16

struct Skeleton : EnemyBase {

	// Constructor
	Skeleton()
	{
		// Setup the enemy
		hp = 2;
		damage = 1;
		name = "Skeleton";
		entity.renderable.m_TextureName = "skeleton";
	}
};