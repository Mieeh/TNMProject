#pragma once

#include<iostream>

#include"../engine/engine.h"
#include"../engine/bear_game.h"
#include"../engine/game_systems.h"

#include"menu.h"

using namespace bear;

struct Game : BearClass
{
	Engine* game; // Engine object

	Menu *menu; // Menu object
	
	// System pointers
	StateSystem *state_system = StateSystem::Instance();

	Game()
	{
		game = new Engine(this); // Create engine instance
	}

	void init() override;
	void update(float dt) override;
	void render() override;
	void on_event(Event& event) override;
	void exit() override;
};
