#pragma once

#include"../../engine/include/level_interface.h"
#include"../../engine/include/game_systems.h"

#include"level_utility.h"

struct Level1 : ILevel {

	std::vector<Entity> entity_list;
	Entity lil;

	void init() override {
		levelUtility_ConvertToEntities(TEST_LEVEL, entity_list);
		std::cout << "glitter" << std::endl;
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
		GraphicsSingleton::Instance()->draw(entity_list);
	}

};