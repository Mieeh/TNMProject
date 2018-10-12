#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include"level_utility.h"

struct Level1 : ILevel {

	LevelContent content;

	void init() override {
		content.tile_map = TEST_LEVEL;
		levelUtility_ConvertToLevelContent(content);

		Player::get()->play_intro_at(core::Vector2i(1, 3));
	}

	void on_event(Event& event) {
		if (event.type == EventType::KeyPressed) {
			if (event.key == Key::X)
				Player::get()->play_intro_at(core::Vector2i(1, 1));
		}
	}

	void update(float dt) override {
		
	}

	void render() override {
		GraphicsSingleton::Instance()->draw(content.walls_floors); // Render all the entities here
	}

	void player_moved() override {

	}

	LevelContent& get_level_content()
	{
		return content;
	}

};