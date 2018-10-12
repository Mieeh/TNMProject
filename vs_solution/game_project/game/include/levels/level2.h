#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"


#include"../player.h"
#include"level_utility.h"

#include<core/vector2.h>

struct Level2 : ILevel {

	LevelContent content;

	void init() {
		content.tile_map = TEST_LEVEL;
		levelUtility_ConvertToLevelContent(content);

		Player::get()->play_intro_at(core::Vector2i(1, 1));
	}


	void update(float dt) {
		
	}

	void render() {
		GraphicsSingleton::Instance()->draw(content.walls_floors);
	}

	void on_event(Event &event) {
		if (event.type == EventType::MousePressed) {
			std::cout << "mouse pressed on level2" << std::endl;
		}
	}

	void player_moved() {
		std::cout << "player moved\n";
	}

	LevelContent& get_level_content()
	{
		return content;
	}

};