#pragma once

#include"../../engine/level/level_interface.h"
#include"../../engine/game_systems.h"

struct Level1 : ILevel {

	void init() override {

	}

	void on_event(Event& event) {
		if (event.type == EventType::KeyPressed) {
			if (event.key == Key::A) {
				LevelManagerSingleton::Instance()->setCurrentLevel("menu");
			}
		}
	}

	void update(float dt) override {
		
	}

	void render() override {

	}

};