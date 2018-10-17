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
// Notes(david) where is top_left/right_walls?!?!

#define GOAL 99
#define G GOAL

#define BAT 7 

#define ENEMIES { BAT }
#define FLOORS_AND_WALLS { FLOOR1, WALL_TOP, PIT, WALL_LEFT, WALL_RIGHT, BOTTOM_LEFT_WALL, BOTTOM_RIGHT_WALL }

static bool is_enemy(int _v) {
	for (int _e : ENEMIES) {
		if (_v == _e)
			return true;
	}
	return false;
}

static bool is_floor_or_wall(int _v) {
	for (int _e : FLOORS_AND_WALLS) {
		if (_v == _e)
			return true;
	}
	return false;
}

static bool is_floor(int _v) {
	for (int _e : { FLOOR1 }) {
		if (_v == _e)
			return true;
	}
	return false;
}

static level_list TEST_LEVEL = 
{
	{ 3, 1, 1, 1, 1,   1, 4 },
	{ 3, 0, 0, 0, 0,   0, 4 },
	{ 3, 0, 0, 0, BAT, 0, 4 },    
	{ 3, 0, 0, 0, 0,   G, 4 },	
	{-1, 2, 2, 2, 2,   2,-1 },
};