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
		content.tile_map = LEVEL2;
		levelUtility_ConvertToLevelContent(content);

		gas_interval = 4;
		gas_offset = -3;

		player->play_intro_at(core::Vector2i(1, 5));

		engine->graphics_manager->view.setPosition(player->world_position);
		engine->graphics_manager->point_to_follow = &player->world_position;

		// Background music
		engine->sound_manager->set_background_music("bg");

		next_level_name = "level3";
	}

	void on_event(Event& event) {
		player->on_event(event);
	}

	void update(float dt) override {
		player->update(dt);
		content.update(dt);
	}

	void render() override {
		player->render();
		engine->graphics_manager->draw(content.walls_floors);
		engine->graphics_manager->draw(content.enemies);
		engine->graphics_manager->draw(content.items);
		engine->graphics_manager->draw(content.presure_plates);
		engine->graphics_manager->draw(content.gates);
		content.spike_system.render();
	}

	void player_moved() override {

	}

	LevelContent& get_level_content()
	{
		return content;
	}

};