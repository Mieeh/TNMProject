#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include"level_utility.h"
#include"../player.h"

struct Level1 : ILevel {

	LevelContent content;
	Player* player = Player::get(); // Update, event, render
	Engine* engine = Engine::Instance();

	void init() override {
		// Load the actual map data
		content.tile_map = TEST_LEVEL;
		levelUtility_ConvertToLevelContent(content);
		
		// Setup the player
		player->play_intro_at(core::Vector2i(1, 1));

		// Signal the camera which point to follows
		engine->graphics_manager->point_to_follow = &player->world_position;
		
		// Set the next level name so we know which level to load!
		next_level_name = "level2";
	}

	void on_event(Event& event) {
		player->on_event(event);
	}

	void update(float dt) override {
		player->update(dt);
	}

	void render() override {
		// Render all the entities here
		player->render();
		engine->graphics_manager->draw(content.enemies);
		engine->graphics_manager->draw(content.walls_floors);
		engine->graphics_manager->draw(content.items);
	}

	void player_moved() override {

	}

	LevelContent& get_level_content()
	{
		return content;
	}

};