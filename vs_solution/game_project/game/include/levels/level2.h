#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include"level_utility.h"
#include "../player.h"

struct Level2 : ILevel {

	LevelContent content;

	void init() override {
		content.tile_map = LEVEL_2;
		levelUtility_ConvertToLevelContent(content);

		Player::get()->play_intro_at(core::Vector2i(1, 2));

		GraphicsSingleton::Instance()->point_to_follow = &Player::get()->world_position;

		next_level_name = "level1";
	}

	void on_event(Event& event) {
		if (event.type == EventType::KeyPressed) {
			if (event.key == Key::X)
				Player::get()->play_intro_at(core::Vector2i(3, 3));
		}
	}

	void update(float dt) override {

	}

	void render() override {
		GraphicsSingleton::Instance()->draw(content.walls_floors); // Render all the entities here
		GraphicsSingleton::Instance()->draw(content.enemies);
	}

	void player_moved() override {

	}

	LevelContent& get_level_content()
	{
		return content;
	}

};