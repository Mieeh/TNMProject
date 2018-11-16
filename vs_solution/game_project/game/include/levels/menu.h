#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"
#include"../../../engine/include/bear_game.h"
#include"../../../engine/include/engine.h"

#include<window\window.h>

struct TitleScreen : ILevel {

	Entity test;
	Engine* engine = Engine::Instance();
	bool start_game;

	void init() override {
		test.renderable.m_TextureName = "titlescreen_wip";
		test.renderable.m_Transform.m_Size = core::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		test.renderable.m_Transform.m_Position = core::Vector2f(0, 0);
		test.renderable.m_Color.a = 1.0f;

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
			test.renderable.m_Transform.m_Size = event.size;
		}
	}

	void update(float dt) override {
		if (start_game == true) {
			test.renderable.m_Transform.m_Position.y -= 0.2f * dt;
			test.renderable.m_Color.a -= 0.00035f*dt;
			if (test.renderable.m_Color.a < 0) {
				engine->sound_manager->get_music("bg")->sf_music.setVolume(engine->config_manager->config_values.at("background_levels"));
				engine->sound_manager->get_music("bg")->sf_music.setLoop(true);
				engine->sound_manager->get_music("bg")->sf_music.play();

				engine->level_manager->setCurrentLevel("level1");
			}
		}
	}

	void render() override {
		engine->graphics_manager->draw(test);
	}

	void player_moved() override {

	}

	LevelContent& get_level_content() override {
		return LevelContent();
	}

};