#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include"level_utility.h"
#include"../player.h"

struct Level1 : ILevel {

	LevelContent content;
	Player* player = Player::get(); // Update, event, render
	Engine* engine = Engine::Instance();
	float cutscene_timer = 0.0f;

	void init() override {
		// Load the actual map data
		content.tile_map = TUTORIAL_LEVEL;
		levelUtility_ConvertToLevelContent(content);
		
		// Set the gas variables
		gas_offset = -1;
		gas_interval = -1;
		
		// Setup the player
		player->play_intro_at(core::Vector2i(1, 5));

		// Signal the camera which point to follows
		engine->graphics_manager->view.setPosition(player->world_position);
		engine->graphics_manager->point_to_follow = &player->world_position;

		// Cutscenetimer reset
		cutscene_timer = 0.0f;
		
		// Set the next level name so we know which level to load!
		next_level_name = "level2";					
	}

	void on_event(Event& event) {
		player->on_event(event);
	}

	void update(float dt) override {
		player->update(dt);

		if (engine->sound_manager->get_sfx("pp_rumble")->sf_sound.getStatus() == sf::SoundSource::Status::Playing) {
			cutscene_timer += 0.1f * dt;
			std::cout << cutscene_timer << std::endl;
		}
	}

	void render() override {
		// Render all the entities here
		player->render();
		engine->graphics_manager->draw(content.enemies);
		engine->graphics_manager->draw(content.walls_floors);
		engine->graphics_manager->draw(content.items);
		engine->graphics_manager->draw(content.presure_plates);
	}

	void player_moved() override {
		if (player->tile_position == core::Vector2i(19, 7)) {
			engine->sound_manager->get_sfx("pp_rumble")->sf_sound.play();
			player->set_player_state(PlayerStates::CUTSCENE); 
		}
	}

	LevelContent& get_level_content()
	{
		return content;
	}

};