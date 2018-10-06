#pragma once

#include<iostream>

#include"../engine/include/engine.h"
#include"../engine/include/bear_game.h"
#include"../engine/include/game_systems.h"

using namespace bear;

struct Game : BearClass
{
	Engine* game; // Engine object

	// Singleton pointers
	LevelManagerSingleton* level_manager = LevelManagerSingleton::Instance(); // Keeping track and managing the current level to play!

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
