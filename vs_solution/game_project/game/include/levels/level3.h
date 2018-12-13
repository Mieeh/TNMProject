#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include"level_utility.h"
#include "../player.h"

#include<fstream>

struct Level3 : ILevel {

	LevelContent content;
	Player* player = Player::get(); // Update, event, render
	Engine* engine = Engine::Instance();

	void init() override {
		content.tile_map = LEVEL3;
		levelUtility_ConvertToLevelContent(content);

		gas_interval = 4;
		gas_offset = -12;
		//gas_offset = -1;
		//gas_interval = 2;

		player->play_intro_at(core::Vector2i(1, 7));

		engine->graphics_manager->view.setPosition(player->world_position);
		engine->graphics_manager->point_to_follow = &player->world_position;

		engine->sound_manager->set_background_music("bg");

		next_level_name = "level1";
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

	void completed_level() override {
		// Do some stuff to indicate the player has completed the game!
		std::ofstream file("GAME_WON.txt");
		file << "You've completed the demo! Thanks for trying the game!" << std::endl;
		file << "Comment 01100100 01110101 01101110 01110111 01100101 01101100 01101100(dunwell) on the Itch.io page!" << std::endl;
		file.close();
	}

};