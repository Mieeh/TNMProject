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
	NO      = -1, // no
	RIGHT   = 0,  // (1, 0)
	LEFT    = 1,  // (-1, 0)
	DOWN    = 2,  // (0, 1)
	UP      = 3   // (0, -1)
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

	// Move directions, used for translating the enum into a direction!
	core::Vector2i move_directions[4] = { core::Vector2i(1,0), core::Vector2i(-1, 0), core::Vector2i(0, 1), core::Vector2i(0, -1) };

public:

	void on_event(Event& event);
	void update(float dt);
	void render();

	void move_player(int move_direction_enum);

public:
	static Player* get();
private:
	Player();
	static Player* instance;
};