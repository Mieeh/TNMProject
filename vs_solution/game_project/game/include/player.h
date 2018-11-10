#pragma once

#include"../../engine/include/entity.h"
#include"../../engine/include/game_systems.h"
#include"../../engine/include/bear_game.h"

#include"death_screen.h"
#include"player_animation.h"
#include"player_ui.h"

#include<window\event.h>
#include<core\vector2.h>

using namespace bear;

#define PLAYER_SIZE 1.6f
#define PLAYER_OFFSET core::Vector2f(-22, -30)

enum PlayerStates {
	INTRO,
	IDLE,
	IN_TRANSIT,
	OUTRO,
	DEAD
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
	int hp = 5;     							
	int attack = 1; 
	core::Vector2i tile_position; 
	core::Vector2f world_position;
	Engine* engine = Engine::Instance();

private:
	const float move_speed = 0.2f;
	const float fall_speed = 0.65;

	Entity entity;
	DeathPanel death_panel;
	PlayerAnimation player_anim;
	std::string last_played_footstep = "footstep1";
	const float footstep_delay = 250;

	// Player ui object
	PlayerUI player_ui;

	Item* current_item = nullptr;

	PlayerStates player_state = PlayerStates::IDLE;
	PlayerMoveDirection move_direction = PlayerMoveDirection::NO;
	bool goal_trigger = false;

	// Move directions, used for translating the enum into a direction!
	core::Vector2i move_directions[4] = { core::Vector2i(1,0), core::Vector2i(-1, 0), core::Vector2i(0, 1), core::Vector2i(0, -1) };

private:
	std::string get_random_footstep(unsigned int number_of_footsteps);

public:

	void on_event(Event& event);
	void update(float dt);
	void render();

	void set_player_position(const core::Vector2i position); // Instantly moves player to position, tile-based
	void set_player_state(PlayerStates new_state); // Sets player_state + some other switching logic between states

	void play_intro_at(const core::Vector2i position);
	void resolve_combat(EnemyBase& enemy, int move_direction_enum);
	void resolve_item(Item& item, int move_direction_enum);
	void reset_after_death();
	void handle_item_use();

	// Per state code methods
	void idle_player_state_control(); // logic for idle state is here
	void move_player_state_control(PlayerMoveDirection dir, float dt); // logic for move state is here
	void move_player(int move_direction_enum); // moves player in direction
	void intro_player(float dt); // does intro 
	void outro_player(float dt); // does outro 

public:
	static Player* get();
private:
	Player();
	static Player* instance;
};