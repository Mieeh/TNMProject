#pragma once

#include<vector>

typedef std::vector<std::vector<int>> level_list;

#define TILE_SIZE 64 // Very important value used alot!

#define FLOOR1 0
#define WALL_BOTTOM_LEFT_CORNER 1
#define WALL_TOP_LEFT_CORNER 2
#define WALL_BOTTOM_RIGHT_CORNER 3
#define WALL_TOP_RIGHT_CORNER 4

static level_list TEST_LEVEL =
{
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0 },
};