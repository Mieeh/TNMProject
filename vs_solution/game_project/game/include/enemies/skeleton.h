#pragma once

#include"../../../engine/include/enemy.h"

#define SKELETON_SIZE_X 1.3
#define SKELETON_SIZE_Y 1.3
#define SKELETON_OFFSET_X -8.6
#define SKELETON_OFFSET_Y -24

struct Skeleton : EnemyBase {
	// Constructor
	Skeleton()
	{
		// Setup the enemy
		hp = 2;
		damage = 1;
		name = "Skeleton";
		entity.renderable.m_TextureName = "skeletonLeft1";
	}

	void take_damage() 
	{
		if (hp == 1) {
			entity.renderable.m_TextureName = "skeletonLeft_damage1";
		}
		else {
			entity.renderable.m_TextureName = "skeleton_dead";
		}
	}
};