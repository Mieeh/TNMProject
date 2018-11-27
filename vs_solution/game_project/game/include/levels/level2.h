#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include"level_utility.h"
#include "../player.h"

struct Level2 : ILevel {

	LevelContent content;
	Player* player = Player::get(); // Update, event, render
	Engine* engine = Engine::Instance();

	void init() override {		
		content.tile_map = TEST_LEVEL;
		levelUtility_ConvertToLevelContent(content);

		gas_interval = -1;
		gas_offset = -1;

		player->play_intro_at(core::Vector2i(1, 1));

		engine->graphics_manager->view.setPosition(player->world_position);
		engine->graphics_manager->point_to_follow = &player->world_position;

		next_level_name = "level1";
	}

	void on_event(Event& event) {
		player->on_event(event);
	}

	void update(float dt) override {
		player->update(dt);
	}

	void render() override {
		player->render();
		engine->graphics_manager->draw(content.walls_floors);
		engine->graphics_manager->draw(content.enemies);
		engine->graphics_manager->draw(content.items);
		engine->graphics_manager->draw(content.presure_plates);
	}

	void player_moved() override {

	}

	LevelContent& get_level_content()
	{
		return content;
	}

};