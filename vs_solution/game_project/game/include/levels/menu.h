#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"
#include"../../../engine/include/bear_game.h"
#include"../../../engine/include/engine.h"

#include<window\window.h>

struct TitleScreen : ILevel {

	Entity pipe;
	Entity title_screen;
	Engine* engine = Engine::Instance();
	bool start_game;

	void init() override {
		title_screen.renderable.m_TextureName = "titlescreen_wip";
		title_screen.renderable.m_Transform.m_Size = core::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		title_screen.renderable.m_Transform.m_Position = core::Vector2f(0, 0);
		title_screen.renderable.m_Color.a = 1.0f;
		
		pipe.renderable.m_TextureName = "wellPipeLong";
		pipe.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE * 16) *2.36;
		pipe.renderable.m_Layer = 5;
		pipe.renderable.m_Transform.m_Position = core::Vector2f((WINDOW_WIDTH / 2)-pipe.renderable.m_Transform.m_Size.x/2, title_screen.renderable.m_Transform.m_Size.y);

		start_game = false;
	}

	void on_event(Event &event) override {
		if (event.type == EventType::KeyPressed) {
			if (event.key == engine->config_manager->key_map.at("INTERACT1")) {
				engine->sound_manager->get_sfx("into_the_well")->sf_sound.play();
				start_game = true;
			}
		}
		if (event.type == EventType::WindowReiszed) {
			title_screen.renderable.m_Transform.m_Size = event.size;
		}
	}

	void update(float dt) override {
		if (start_game == true) {
			title_screen.renderable.m_Transform.m_Position.y -= 0.2f * dt;
			pipe.renderable.m_Transform.m_Position.y -= 0.2f * dt;
			title_screen.renderable.m_Color.a -= 0.00035f*dt;
			pipe.renderable.m_Color.a -= 0.00035f*dt;

			if (title_screen.renderable.m_Color.a < 0) {
				engine->sound_manager->get_music("bg")->sf_music.setVolume(engine->config_manager->config_values.at("background_levels"));
				engine->sound_manager->get_music("bg")->sf_music.setLoop(true);
				engine->sound_manager->get_music("bg")->sf_music.play();

				engine->level_manager->setCurrentLevel("level1");
			}
		}
	}

	void render() override {
		engine->graphics_manager->draw(title_screen);
		engine->graphics_manager->draw(pipe);
	}

	void player_moved() override {

	}

	LevelContent& get_level_content() override {
		return LevelContent();
	}

};