#include"include/game.h"

#include"include/levels/level1.h"
#include"include/levels/level2.h"
#include"include/levels/menu.h"

#include"../engine/include/game_systems.h"

void Game::init()
{
	// Register levels
	Engine::Instance()->level_manager->registerLevel("level1", new Level1);
	Engine::Instance()->level_manager->registerLevel("level2", new Level2);
	Engine::Instance()->level_manager->registerLevel("menu", new TitleScreen);

	/*
	float music_volume = Engine::Instance()->config_manager->config_values.at("background_levels");
	Engine::Instance()->sound_manager->get_music("bg")->sf_music.setVolume(music_volume);
	Engine::Instance()->sound_manager->get_music("bg")->sf_music.setLoop(true);
	Engine::Instance()->sound_manager->get_music("bg")->sf_music.play();
	*/

	Engine::Instance()->sound_manager->setSFX_Volumes(Engine::Instance()->config_manager->config_values.at("sfx_levels"));

	// Set current level
	Engine::Instance()->level_manager->setCurrentLevel("menu");
}

void Game::update(float dt) {
	Engine::Instance()->graphics_manager->update(dt);
	Engine::Instance()->level_manager->update_current_level(dt);
}

void Game::render() {
	Engine::Instance()->level_manager->render_current_level();
}

void Game::on_event(Event& event) {
	Engine::Instance()->level_manager->on_event_current_level(event);
}

void Game::exit()
{

}