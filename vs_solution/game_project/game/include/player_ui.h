#pragma once

#include"../../engine/include/bear_game.h"
#include"../../engine/include/entity.h"

class Player;

struct PlayerUI {

	// Members
	Player *player;
	Engine* engine;
	Entity food_entities[5];

	// Constructor
	PlayerUI();

	// Methods

	// Renders player hp based on the players current hp
	void render_player_hp();

};