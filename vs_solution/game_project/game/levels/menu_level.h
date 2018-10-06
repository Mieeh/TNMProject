#pragma once

#include"../../engine/include/level_interface.h"

struct MenuLevel : ILevel {


	void init() override
	{

	}

	void on_event(Event& event) override
	{
		if (event.type == EventType::KeyPressed) {
			if (event.key == Key::X) {
				LevelManagerSingleton::Instance()->setCurrentLevel("level1");
			}
		}
	}

	void update(float dt) override
	{
	}

	void render() override
	{

	}
};