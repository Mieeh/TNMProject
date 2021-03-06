#pragma once

#include<iostream>

#include"../../engine/include/engine.h"
#include"../../engine/include/bear_game.h"
#include"../../engine/include/game_systems.h"

#include"player.h"

using namespace bear;

struct Game : BearClass
{
	// Singleton pointers				 
	Player* player = Player::get();

	Game()
	{
		Engine::Instance()->init(this);
	}

	void init() override;
	void update(float dt) override;
	void render() override;
	void on_event(Event& event) override;
	void exit() override;
};