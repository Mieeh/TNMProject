#pragma once

#include"../../engine/include/entity.h"
#include"../../engine/include/game_systems.h"

#include<window\event.h>
#include<core\vector2.h>

using namespace bear;

enum PlayerStates {
	IDLE,
	IN_TRANSIT
};

class Player {

private:
	// Player members 
	LevelManagerSingleton *level_manager_singleton = LevelManagerSingleton::Instance();
	Entity entity;
	PlayerStates player_state = PlayerStates::IDLE;

public:
	core::Vector2i tile_position;
	core::Vector2i world_position;

	void on_event(Event& event);
	void update(float dt);
	void render();

	void set_position(const core::Vector2i& new_position);
	void player_move(const core::Vector2i& walk_direction);

public:
	static Player* get();
private:
	Player();
	static Player* instance;
};