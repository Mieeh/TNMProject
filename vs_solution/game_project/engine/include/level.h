#pragma once

#include<window/event.h>
using namespace bear;

#include<vector>
typedef std::vector<std::vector<int>> level_list;

// Forward decleration
struct Item;
struct IEnemy;

// Structure for data that every level has // @PROTOTYPE
struct LevelContent {
	level_list tile_map;
	std::vector<Entity> walls_floors;
	//std::map<core::Vector2i, Item> items;
	//std::map<core::Vector2i, IEnemy> enemies;
};

struct ILevel {
	virtual void init() = 0; // Called when a level is started
	virtual void on_event(Event& event) = 0; // Called every event
	virtual void update(float dt) = 0; // Called ones each frame used to update game logic
	virtual void render() = 0; // Do rendering here
	virtual void player_moved() = 0; // Called when the player moves!
	virtual LevelContent& get_level_content() = 0;
};