#pragma once

#include<vector>

typedef std::vector<std::vector<int>> level_list;

#define TILE_SIZE 64 // Very important value used alot!

#define FLOOR1 0
#define WALL_TOP 1
#define PIT 2
#define WALL_LEFT 3
#define WALL_RIGHT 4
#define BOTTOM_LEFT_WALL 5
#define BOTTOM_RIGHT_WALL 6

static level_list TEST_LEVEL =
{
	{ 3, 1, 1, 1, 1, 1, 4 },
	{ 3, 0, 0, 0, 0, 0, 4 },
	{ 3, 0, 0, 0, 0, 0, 4 },    
	{ 3, 0, 0, 0, 0, 0, 4 },	
	{ 5, 0, 0, 0, 0, 0, 6 },
	{-1, 2, 2, 2, 2, 2, -1 },
};