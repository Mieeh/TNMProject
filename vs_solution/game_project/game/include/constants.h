#pragma once

#include<vector>

typedef std::vector<std::vector<int>> level_list;

#define TILE_SIZE 64 // Very important value used alot!

#define LAYER0 1
#define LAYER1 10
#define LAYER2 100
#define LAYER3 1000

#define FLOOR1 0
#define WALL_TOP 1
#define PIT 2
#define WALL_LEFT 3
#define WALL_RIGHT 4
#define LEFT_WALL_PIT 5
#define RIGHT_WALL_PIT 6
#define LWP LEFT_WALL_PIT 
#define RWP RIGHT_WALL_PIT

#define GOAL 99
#define G GOAL

#define ITEM 2000
#define WI ITEM+0 // Weapon Item
#define HI ITEM+1 // Health Item
#define SI ITEM+2 // Shield Item
#define KI ITEM+3 // Key    Item
#define PP ITEM+4 // Presure (Not Item) But still for ease of use we categorise it as an item
#define RK ITEM+5 // Red-key

#define GATES ITEM+50
#define GATES_RED GATES+50
#define GATE_FACING_LEFT GATES+0
#define GATE_FACING_RIGHT GATES+1
#define GATE_FACING_DOWN GATES+2
#define GATE_FACING_UP GATES+3
#define GFL GATE_FACING_LEFT
#define GFR GATE_FACING_RIGHT
#define GFD GATE_FACING_DOWN
#define GFU GATE_FACING_UP

// Red gates
#define GFR_R GFR+GATES_RED
#define GFL_R GFL+GATES_RED
#define GFD_R GFD+GATES_RED
#define GFU_R GFU+GATES_RED

#define GATES_LIST {GFL, GFR, GFD, GFU, GFR_R, GFL_R, GFD_R, GFU_R }
#define GATES_LIST_RED { GFR_R, GFL_R, GFD_R, GFU_R } // Just the reds

#define SPIKE ITEM+10
#define SP SPIKE

#define SKE 7

#define ENEMIES { SKE }
#define FLOORS_AND_WALLS { FLOOR1, WALL_TOP, PIT, WALL_LEFT, WALL_RIGHT, GOAL, RWP, LWP }
#define ITEMS { WI, HI, SI, KI, RK }

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

static bool is_item(int _v) {
	for (int _e : ITEMS) {
		if (_v == _e) {
			return true;
		}
	}
	return false;
}

static bool is_pp(int _v) {
	if (_v == PP) {
		return true;
	}
	return false;
}

static bool is_gate(int _v) {
	for (int _e : GATES_LIST) {
		if (_e == _v) {
			return true;
		}
	}
	return false;
}

static bool is_gate_red(int _v) {
	for (int _e : GATES_LIST_RED) {
		if (_e == _v) {
			return true;
		}
	}
	return false;
}

static level_list TUTORIAL_LEVEL =
{															
	{ -1,-1,-1,-1,-1, -1,-1,-1, 3, 1,  1, 1, 4,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
	{ -1,-1,-1,-1,-1, -1,-1,-1, 3, 0, KI, 0, 4,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
	{ -1,-1,-1,-1,-1, -1,-1,-1, 3, 2,  0, 2, 4,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
	{ 3, 1, 1, 1, 4, -1,-1,-1, 3,-1,SKE,-1, 4,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
	{ 3, 0, 0, 0, 1,  1, 1, 1, 1, 0,  0, 0, 4,-1,-1,  -1,-1,-1,-1,-1, 3, 1, 1, 1, 4 },
	{ 3, 0, 0, 0, 0,SKE, 0,HI, 0,SI,  0, 0, 1, 1, 1,   1, 1, 1, 1, 1, 1, 0, 0, 0, 4 },
	{ 3, 0, 0, 0, 2,  2, 2, 2, 2, 0,  0, 0, GFL,  0,PP,0, 0, 0, 0, 0, 0, 0, G, 0, 4 }, 
	{ -1, 2, 2, 2,-1, -1,-1,-1,-1, 2,  2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 0, 0, 0, 4 },
	{ -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1, 2, 2, 2,-1 },
};

static level_list LEVEL2 =
{    // 23/10 Start at 1,5
	{-1,-1,-1,-1,-1,-1,-1,-1, -1,-1, -1,-1,   3, 1, 1,  1,     1,  4,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1, -1,-1, -1,-1,   3, 2, 2,  0,     KI, 4,-1,-1,-1,-1,-1},
	{ 3, 1, 1, 1, 1, 1, 1, 1,  4, 3,  1, 1,   1,-1,-1, SP,     2,  4, 3, 1, 1, 1, 4},
	{ 3, 2, 0, 0, 2, 2, 2, 2,  4, 3,SKE, GFL, 0, 0, 0,SKE,     0,  1, 1, 0, 0, 0, 4},
	{ 3,-1, 2, 2,-1, 0, 0,-1,  1, 1,  0,RWP,LWP,HI, 0,  2,     0, SKE, GFL, 0, G, 0, 4},
	{ 3, 0, 0, 0, 0,WI, 0, 0,SKE, 0,  0, 4,   3, 2, 0, -1,     2,  2, 2, 0, 0, 0, 4},
	{ 3, 2, 2, 2, 0, 0, 0, 2,  2,LWP, 0, 4,   3,HI, 0,  SP,    0,  4,-1, 2, 2, 2,-1},
	{ 3,-1,-1,-1, 2, 2, 0,-1, -1, 3, KI, 4,   3, 0, 2,  0,     0,  1, 1, 1, 1, 4,-1},
	{-1,-1,-1,-1,-1,-1, 2,-1, -1,-1,  2,-1,   3, 0, 0,  0,     0,SKE, HI,HI,WI, 4,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1, -1,-1, -1,-1,-  1, 2, 2,  2,     2,  2, 2, 2, 2,-1,-1},
};

static level_list LEVEL3 =
{ // 21/21 Start at 1,7
	{-1,    -1,-1,-1,-1, 3, 1, 1,  1, 1,  1, 1,  1, 1,   1, 1,  1, 1, 1,  4,-1},
	{-1,    -1,-1,-1,-1, 3, 0, 0,  0, 0, SP, 0,  0, 0,   0, 0,  0,SP,SI,  4,-1},
	{-1,    -1,-1,-1,-1, 3, 0, 0, SP, 0,  0,SP,  0, 0,  SP, 0, SP, 0,SP,  4,-1},
	{-1,    -1,-1,-1,-1, 3, 0,SP,  0,SP,  0,SP,SKE, 0,   0, 0, SP, 0, 0,  4,-1},
	{-1,    -1,-1,-1,-1, 3,SP, 0, HI,LWP, 1, 1,GFU, 1,   1,RWP,  0, 0, 0, 4,-1},
	{-1,    -1,-1,-1,-1, 3, 0, 0,  0, 3,  0, 0,SKE, 0,   0, 4, SP, 0, 0,  4,-1},
	{ 3,     1, 1, 1, 1, 1, 0, 0,  0, 3,  0, 2,GFU_R, 2, 0, 4,  0,SP, 0,  4,-1},
	{ 3, 0, 0, 0, 0, 0, 0,WI,SKE,GFL,SKE,GFL_R,G,GFR_R,SKE,GFR,SKE, 0,SP, 4,-1},
	{-1,    2, 2, 2, 2,LWP,0, 0,  0,LWP,  0, 2,GFD, 2,   0,RWP,  0,WI, 0, 4,-1},
	{-1,    -1,-1,-1,-1, 3, 0, 0,  0, 3,  0, 0,SKE, 0,   0, 4, SP,SP, 0,  4,-1},
	{-1,    -1,-1,-1,-1, 3, 0, 0, SP, 0,  2, 2,  2, 2,   2, 0,  0, 0, 0,  4,-1},
	{-1,    -1,-1,-1,-1, 3, 0, 0, SP,RK, -1,-1, -1,-1,  -1,KI,  0, 0,SP,  4,-1},
	{-1,    -1,-1,-1,-1, 3, 0, 0, SP, 0, -1,-1, -1,-1,  -1, 0,  0, 0, 0,  4,-1},
	{-1,    -1,-1,-1,-1,-1, 2, 2,  2, 2, -1,-1, -1,-1,  -1, 2,  2, 2, 2, -1,-1},
};

static level_list LEVEL4 =
{ // 25/24 Start at 1,2
	{-1,-1,-1,-1,-1, 3, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1, 1, 1,  4,-1,-1,-1,-1,-1,-1,},
	{ 3, 1, 1, 1, 1, 1, 0, 0, 0, 2, 2,  0,  2,  2,  2,  2, 2, 2,  4, 3, 1, 1, 1, 4,-1,},
	{ 3, 0, 0, 0, 0, 0, 0,KI, 0, 0, 0, WI, SP,SKE, SKE, -1,-1,-1,  1, 1, 0, 0, 0, 4,-1,},
	{-1, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2,  0,  2,  2, SP,SKE, 0, 0,GFL, 0, 0, G, 0, 4,-1,},
	{-1,-1,-1,-1,-1,-1, 2,SP, 2,-1,-1,SKE, SP,SKE,  2,  0, 2, 2,  2, 2, 0, 0, 0, 4,-1,},
	{-1,-1,-1,-1,-1,-1,-1,HI, 0, 0, 0,  0,  2,  0,  0,  0,-1,-1, -1,-1, 2, 2, 2,-1,-1,},
	{-1,-1,-1,-1,-1,-1,-1, 2, 2, 0, 2,  0,SKE,  0,  2,  0,-1,-1, -1,-1,-1,-1,-1,-1,-1,},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 0,HI,  2,  0,  2, -1, SI,-1,-1, -1,-1,-1,-1,-1,-1,-1,},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 2, 0,  0,  0, -1, -1,  2,-1,-1, -1,-1,-1,-1,-1,-1,-1,},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 2,  2,  2, -1, -1, -1,-1,-1, -1,-1,-1,-1,-1,-1,-1,},
};