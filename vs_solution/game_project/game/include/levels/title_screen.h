#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include"../../../engine/include/bear_game.h"

struct TitleScreen : ILevel {

	Engine *engine = Engine::Instance();
	Entity title_screen;
	Entity long_pipe;
	Entity fade_panel;
	bool game_start = false;

	const float magic_well_constant = 0.165f;

	void init() override {
		title_screen.renderable.m_TextureName = "titlescreen_wip";
		title_screen.renderable.m_Transform.m_Size = core::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		
		fade_panel.renderable.m_Transform.m_Size = core::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		fade_panel.renderable.m_Color = core::Color::Black();
		fade_panel.renderable.m_Color.a = 0.0f;

		long_pipe.renderable.setTextureNameWData("wellPipeLong");
		long_pipe.renderable.m_Transform.m_Size.x = WINDOW_WIDTH * magic_well_constant;
		long_pipe.renderable.m_Transform.m_Size.y = long_pipe.renderable.m_Transform.m_Size.x * 16;
		long_pipe.renderable.m_Transform.m_Position = core::Vector2f((WINDOW_WIDTH / 2) - (long_pipe.renderable.m_Transform.m_Size.x / 2), WINDOW_HEIGHT);
	}

	void on_event(Event &event) override {
		if (event.key == engine->config_manager->key_map.at("INTERACT1")) {
			engine->sound_manager->get_sfx("into_the_well")->sf_sound.play();
			game_start = true;
		}
		if (event.type == EventType::WindowReiszed) {
			fade_panel.renderable.m_Transform.m_Size = event.size;
			title_screen.renderable.m_Transform.m_Size = event.size;
			long_pipe.renderable.m_Transform.m_Size.x = event.size.x * magic_well_constant;
			long_pipe.renderable.m_Transform.m_Size.y = long_pipe.renderable.m_Transform.m_Position.x * 16;
			long_pipe.renderable.m_Transform.m_Position = core::Vector2f((event.size.x / 2) - (long_pipe.renderable.m_Transform.m_Size.x / 2), event.size.y);
		}
	}

	void update(float dt) override {
		if (game_start) {
			long_pipe.renderable.m_Transform.m_Position.y -= 0.2f * dt;
			title_screen.renderable.m_Transform.m_Position.y -= 0.2f * dt;
			fade_panel.renderable.m_Color.a += 0.00040f * dt;
			if (fade_panel.renderable.m_Color.a >= 1.2f) {
				// Start the game!
				float music_volume = Engine::Instance()->config_manager->config_values.at("background_levels");
				Engine::Instance()->sound_manager->get_music("bg")->sf_music.setVolume(music_volume);
				Engine::Instance()->sound_manager->get_music("bg")->sf_music.setLoop(true);
				Engine::Instance()->sound_manager->get_music("bg")->sf_music.play();
				engine->level_manager->setCurrentLevel("level1");
			}
		}
	}

	void render() override {
		engine->graphics_manager->draw(title_screen);
		engine->graphics_manager->draw(long_pipe);
		engine->graphics_manager->draw_as_ui(fade_panel);
	}

	void player_moved() override {

	}

	LevelContent& get_level_content()
	{
		return LevelContent();
	}

};