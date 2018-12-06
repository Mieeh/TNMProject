#pragma once

#include"../../../engine/include/level.h"
#include"../../../engine/include/game_systems.h"

#include"../../../engine/include/bear_game.h"

struct TitleScreen : ILevel {

	Engine *engine = Engine::Instance();
	Entity title_screen;
	Entity long_pipe;
	Entity logo;
	Entity press_any_key;
	Entity credits;
	Entity fade_panel;
	bool game_start = false;

	const float magic_well_constant = 0.165f;
	const float fade_speed = 0.001f;

	void init() override {
		title_screen.renderable.m_TextureName = "titlescreen";
		title_screen.renderable.m_Transform.m_Size = core::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		
		fade_panel.renderable.m_Transform.m_Size = core::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
		fade_panel.renderable.m_Color = core::Color::Black();
		fade_panel.renderable.m_Color.a = 0.0f;

		// Logo entity & press_any_key & credits
		logo.renderable.setTextureNameWData("logo");
		logo.renderable.m_Transform.m_Size = logo.renderable.m_Transform.m_Size * 0.5f;
		logo.renderable.m_Transform.m_Position = core::Vector2f((WINDOW_WIDTH / 2) - (logo.renderable.m_Transform.m_Size.x / 2), 35);
		logo.renderable.m_Layer = 10;

		press_any_key.renderable.setTextureNameWData("titleprompt");
		press_any_key.renderable.m_Transform.m_Size = press_any_key.renderable.m_Transform.m_Size * 0.5f;
		press_any_key.renderable.m_Transform.m_Position = core::Vector2f((WINDOW_WIDTH / 2) - (press_any_key.renderable.m_Transform.m_Size.x / 2), 70 + logo.renderable.m_Transform.m_Size.y);
		press_any_key.renderable.m_Layer = 10;

		credits.renderable.setTextureNameWData("credits");
		credits.renderable.m_Transform.m_Size = credits.renderable.m_Transform.m_Size * 0.5f;
		credits.renderable.m_Transform.m_Position = core::Vector2f(0, WINDOW_HEIGHT - credits.renderable.m_Transform.m_Size.y);
		credits.renderable.m_Layer = 10;

		logo.renderable.m_Color.a = 0.0f;
		press_any_key.renderable.m_Color.a = 0.0f;
		credits.renderable.m_Color.a = 0.0f;

		long_pipe.renderable.setTextureNameWData("wellPipeLong");
		long_pipe.renderable.m_Transform.m_Size.x = WINDOW_WIDTH * magic_well_constant;
		long_pipe.renderable.m_Transform.m_Size.y = long_pipe.renderable.m_Transform.m_Size.x * 16;
		long_pipe.renderable.m_Transform.m_Position = core::Vector2f((WINDOW_WIDTH / 2) - (long_pipe.renderable.m_Transform.m_Size.x / 2), WINDOW_HEIGHT);
		
		float music_volume = Engine::Instance()->config_manager->config_values.at("background_levels");
		engine->sound_manager->get_music("title_screen")->sf_music.setVolume(music_volume);					
		engine->sound_manager->get_music("title_screen")->sf_music.play();
	}

	void on_event(Event &event) override {
		if (!game_start) {
			if (event.key == engine->config_manager->key_map.at("INTERACT1")) {
				engine->sound_manager->get_sfx("press_start")->sf_sound.play();
				engine->sound_manager->get_sfx("into_the_well")->sf_sound.play();
				engine->sound_manager->get_music("title_screen")->sf_music.stop();
				game_start = true;
			}
		} 
		if (event.type == EventType::WindowReiszed) {
			float zoom = graphics::Graphics::get_zoom();
			fade_panel.renderable.m_Transform.m_Size = event.size * zoom;
			title_screen.renderable.m_Transform.m_Size = event.size * zoom;

			logo.renderable.m_Transform.m_Position = core::Vector2f((event.size.x*zoom / 2) - (logo.renderable.m_Transform.m_Size.x / 2), 35);
			press_any_key.renderable.m_Transform.m_Position = core::Vector2f((event.size.x*zoom / 2) - (press_any_key.renderable.m_Transform.m_Size.x / 2), 70 + logo.renderable.m_Transform.m_Size.y);
			credits.renderable.m_Transform.m_Position = core::Vector2f(0, (event.size.y*zoom) - credits.renderable.m_Transform.m_Size.y);

			long_pipe.renderable.m_Transform.m_Size.x = event.size.x * magic_well_constant * zoom;
			long_pipe.renderable.m_Transform.m_Size.y = long_pipe.renderable.m_Transform.m_Position.x * 16;
			long_pipe.renderable.m_Transform.m_Position = core::Vector2f(((event.size.x * zoom) / 2) - (long_pipe.renderable.m_Transform.m_Size.x / 2), event.size.y * zoom);
		}
	}

	void update(float dt) override {
		if (game_start) {
			// Fade the stuff
			logo.renderable.m_Color.a -= fade_speed * dt;
			credits.renderable.m_Color.a -= fade_speed * dt;
			press_any_key.renderable.m_Color.a -= fade_speed * dt;
			if (logo.renderable.m_Color.a <= 0.0f) {
				long_pipe.renderable.m_Transform.m_Position.y -= 0.25f * dt;
				title_screen.renderable.m_Transform.m_Position.y -= 0.25f * dt;
				fade_panel.renderable.m_Color.a += 0.00050f * dt;
				if (fade_panel.renderable.m_Color.a >= 1.15f) {
					// Start the game!
					engine->level_manager->setCurrentLevel("level1");
				}
			}
		}
		else {
			if (logo.renderable.m_Color.a < 1) {
				logo.renderable.m_Color.a += fade_speed/2 * dt;
				credits.renderable.m_Color.a += fade_speed/2 * dt;
				press_any_key.renderable.m_Color.a += fade_speed/2 * dt;
			}
			else {
				logo.renderable.m_Color.a = 1.0f;
				credits.renderable.m_Color.a = 1.0f;
				press_any_key.renderable.m_Color.a = 1.0f;
			}
		}
	}

	void render() override {
		engine->graphics_manager->draw(title_screen);
		engine->graphics_manager->draw(long_pipe);
		engine->graphics_manager->draw_as_ui(fade_panel);
		engine->graphics_manager->draw(logo);
		engine->graphics_manager->draw(press_any_key);
		engine->graphics_manager->draw(credits);
	}

	void player_moved() override {

	}

	LevelContent& get_level_content()
	{
		return LevelContent();
	}

};