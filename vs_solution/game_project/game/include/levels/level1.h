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
	bool intro_shake_flag;
	bool intro_camera_flag;
	bool intro_gas_flag;
	bool intro_end_flag;
	core::Vector2f intro_camera_position;

	void init() override {
		// Load the actual map data
		content.tile_map = TUTORIAL_LEVEL;
		levelUtility_ConvertToLevelContent(content);
		
		// Set the gas variables
		gas_offset = -3;
		gas_interval = -1;
		
		// Setup the player
		player->play_intro_at(core::Vector2i(1, 5));
		//player->play_intro_at(core::Vector2i(1, 7));

		// Signal the camera which point to follows
		engine->graphics_manager->view.setPosition(player->world_position);
		engine->graphics_manager->point_to_follow = &player->world_position;

		// Reset cutscene
		cutscene_timer = 0.0f;
		intro_shake_flag = false;
		intro_camera_flag = false;
		intro_gas_flag = false;
		intro_end_flag = false;

		// Background music
		engine->sound_manager->set_background_music("ambience_tutorial");
		
		// Set the next level name so we know which level to load!
		next_level_name = "level2";					
	}

	void on_event(Event& event) {
		player->on_event(event);
	}

	void update(float dt) override {
		player->update(dt);
		content.update(dt); // Updates spikes & doors

		if (engine->sound_manager->get_sfx("pp_rumble")->sf_sound.getStatus() == sf::SoundSource::Status::Playing) {
			cutscene_timer += 0.1f * dt;

			// Start the camera shake
			if (cutscene_timer >= 190 && !intro_shake_flag) {
				intro_shake_flag = true;
				//engine->perform_window_shake(3900, 3);
				engine->graphics_manager->perform_view_shake(3900, 6);
			}
			// Start the gas
			if (cutscene_timer >= 0 && !intro_gas_flag) {
				intro_gas_flag = true;
				// Start the gas moving towards the player yo
				player->gas.current_x = 12;
			}
			// Move the camera left
			if (cutscene_timer >= 210 && !intro_camera_flag) {
				intro_camera_flag = true;
				// Move the camera a bit to the left
				intro_camera_position = player->world_position - core::Vector2f(200, 0);
				engine->graphics_manager->point_to_follow = &intro_camera_position;
			}
			// End 
			if (cutscene_timer >= 600 && !intro_end_flag) {
				intro_end_flag = true;
				// Reset camera
				engine->graphics_manager->point_to_follow = &player->world_position;
				// Gas interval
				player->gas.step_interval = 1;
				player->move_lock = false;
				// Start the music
				engine->sound_manager->set_background_music("mist_first_encounter");
			}
		}
	}

	void render() override {
		// Render all the entities here
		player->render();
		engine->graphics_manager->draw(content.enemies);
		engine->graphics_manager->draw(content.walls_floors);
		engine->graphics_manager->draw(content.items);
		engine->graphics_manager->draw(content.presure_plates);
		content.spike_system.render();
		engine->graphics_manager->draw(content.gates);
	}

	void player_moved() override {
		if (player->tile_position == core::Vector2i(14, 6) && !intro_end_flag) {
			// Play the pp + rumble sfx
			player->move_lock = true;
			engine->sound_manager->stop_background_music();
			engine->sound_manager->get_sfx("pp_rumble")->sf_sound.play();
			player->gas.gas_speed = GAS_MOVE_SPEED * 1.075f;
		}
	}

	LevelContent& get_level_content()
	{
		return content;
	}

};