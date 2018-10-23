#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include<window\window.h>

struct TitleScreen : ILevel {

	Entity test;

	void init() override {
		test.renderable.m_Color = core::Color::Red();
		test.renderable.m_Transform.m_Size = core::Vector2f(100, 100);
	}

	void on_event(Event &event) override {
		if (event.type == EventType::KeyPressed) {
			if (event.key == Key::X) {
				LevelManagerSingleton::Instance()->setCurrentLevel("level1");
			}
		}
	}

	void update(float dt) override {

	}

	void render() override {
		GraphicsSingleton::Instance()->draw(test);
	}

	void player_moved() override {

	}

	LevelContent& get_level_content() override {
		return LevelContent();
	}

};