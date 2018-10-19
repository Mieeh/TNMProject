#pragma once

#include"../../engine/include/entity.h"
#include"../../engine/include/game_systems.h"

#include<window\event.h>
#include<core\vector2.h>

using namespace bear;

enum PlayerStates {
	INTRO,
	IDLE,
	IN_TRANSIT,
	OUTRO
};

enum PlayerMoveDirection {
	NO      = -1, // no
	RIGHT   = 0,  // (1, 0)
	LEFT    = 1,  // (-1, 0)
	DOWN    = 2,  // (0, 1)
	UP      = 3   // (0, -1)
};

class Player {

public:
	// Gameplay related
	int hp = 5;     // Notes(david) what is this actually supposed to be?								
	int attack = 1; // Notes(david) what is this actually supposed to be?
	core::Vector2i tile_position; 
	core::Vector2f world_position;

private:
	const float move_speed = 0.5f;
	const float fall_speed = 0.65;
	LevelManagerSingleton *level_manager_singleton = LevelManagerSingleton::Instance();

	Entity entity;
	
	PlayerStates player_state = PlayerStates::IDLE;
	PlayerMoveDirection move_direction = PlayerMoveDirection::NO;
	bool goal_trigger = false;

	// Move directions, used for translating the enum into a direction!
	core::Vector2i move_directions[4] = { core::Vector2i(1,0), core::Vector2i(-1, 0), core::Vector2i(0, 1), core::Vector2i(0, -1) };

public:

	void on_event(Event& event);
	void update(float dt);
	void render();

	void move_player(int move_direction_enum); // moves player in direction
	void set_player_position(const core::Vector2i position); // Instantly moves player to position, tile-based
	void set_player_state(PlayerStates new_state); // Sets player_state + some other switching logic between states

	void move_player_state_control(PlayerMoveDirection dir, float dt); // logic for move state is here
	void idle_player_state_control(); // logic for idle state is here
	void play_intro_at(const core::Vector2i position);

public:
	static Player* get();
private:
	Player();
	static Player* instance;
};