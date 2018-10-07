#pragma once

#include"../../engine/include/entity.h"
#include"../../engine/include/game_systems.h"

#include<window\event.h>
#include<core\vector2.h>

using namespace bear;

class Player {

private:
	// Player members 
	LevelManagerSingleton *levelManagerSingleton = LevelManagerSingleton::Instance();
	Entity entity;

public:
	core::Vector2i position;

	void on_event(Event& event);
	void update(float dt);
	void render();
	void player_move(const core::Vector2i& walk_direction);

public:
	static Player* get();
private:
	Player();
	static Player* instance;
};