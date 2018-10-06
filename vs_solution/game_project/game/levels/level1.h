#pragma once

#include"../../engine/include/level_interface.h"
#include"../../engine/include/game_systems.h"

#include"level_utility.h"

struct Level1 : ILevel {

	std::vector<Entity> entity_list;

	void init() override {
		levelUtility_ConvertToEntities(TEST_LEVEL, entity_list); // Get the level entities here
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
		GraphicsSingleton::Instance()->draw(entity_list); // Render all the entities here
	}

};