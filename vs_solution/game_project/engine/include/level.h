#pragma once

#include<core\vector2.h>
#include<window/event.h>
using namespace bear;

#include<vector>
#include<map>
typedef std::vector<std::vector<int>> level_list;

#include"enemy.h"
#include"item.h"
#include"presure_plate.h"
#include"spike_system.h"
#include"gate.h"

// Structure for data that every level has /
struct LevelContent {
	core::Vector2i goal_pos;
	level_list tile_map;
	std::vector<Entity> walls_floors;
	std::map<std::string, PresurePlate> presure_plates;
	std::map<std::string, Item> items;
	std::map<std::string, EnemyBase> enemies;
	SpikeSystem spike_system;
	std::vector<core::Vector2i> spike_tile_list;
	std::map<std::string, Gate> gates;

	void update(float dt);
};

struct ILevel {

	std::string next_level_name;
	int gas_offset;
	int gas_interval;

	virtual void init() = 0; // Called when a level is started
	virtual void on_event(Event& event) = 0; // Called every event
	virtual void update(float dt) = 0; // Called ones each frame used to update game logic
	virtual void render() = 0; // Do rendering here
	virtual void player_moved() = 0; // Called when the player moves!
	virtual LevelContent& get_level_content() = 0;
};