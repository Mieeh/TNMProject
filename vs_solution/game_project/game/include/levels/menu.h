#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"
#include"../../../engine/include/bear_game.h"

#include<window\window.h>

struct TitleScreen : ILevel {

	Entity test;
	Engine* engine = Engine::Instance();

	void init() override {
		test.renderable.m_Color = core::Color::Red();
		test.renderable.m_Transform.m_Size = core::Vector2f(100, 100);
	}

	void on_event(Event &event) override {
		if (event.type == EventType::KeyPressed) {
			if (event.key == engine->config_manager->key_map.at("INTERACT1")) {
				engine->level_manager->setCurrentLevel("level1");
			}
		}
	}

	void update(float dt) override {

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