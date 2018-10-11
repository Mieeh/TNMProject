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

enum PlayerMoveDirection {
	NO, // no
	RIGHT, // (1, 0)
	LEFT,  // (-1, 0)
	DOWN,  // (0, 1)
	UP     // (0, -1)
};

class Player {

private:
	// Player members 
	const float move_speed = 0.5f;
	LevelManagerSingleton *level_manager_singleton = LevelManagerSingleton::Instance();
	
	Entity entity;
	
	PlayerStates player_state = PlayerStates::IDLE;
	PlayerMoveDirection move_direction = PlayerMoveDirection::NO;

	core::Vector2i tile_position; 
	core::Vector2f world_position;

	const core::Vector2i RIGHT = core::Vector2i(1, 0);
	const core::Vector2i LEFT = core::Vector2i(-1, 0);
	const core::Vector2i DOWN = core::Vector2i(0, 1);
	const core::Vector2i UP = core::Vector2i(0, -1);

public:

	void on_event(Event& event);
	void update(float dt);
	void render();

	void move_player(const core::Vector2i direction);

public:
	static Player* get();
private:
	Player();
	static Player* instance;
};