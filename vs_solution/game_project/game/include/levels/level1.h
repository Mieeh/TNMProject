#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include"level_utility.h"
#include"../player.h"

struct Level1 : ILevel {

	LevelContent content;
	Player* player = Player::get(); // Update, event, render

	void init() override {
		// Load the actual map data
		content.tile_map = TEST_LEVEL;
		levelUtility_ConvertToLevelContent(content);
		
		// Setup the player
		Player::get()->play_intro_at(core::Vector2i(1, 1));

		// Signal the camera which point to follows
		GraphicsSingleton::Instance()->point_to_follow = &Player::get()->world_position;
		
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
		GraphicsSingleton::Instance()->draw(content.enemies);		// Render enemies
		GraphicsSingleton::Instance()->draw(content.walls_floors);  // Render walls & floors
	}

	void player_moved() override {
	
	}

	// Getter for the level content
	LevelContent& get_level_content()
	{
		return content;
	}

};