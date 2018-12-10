#include"include/game.h"

#include"include/levels/level1.h"
#include"include/levels/level2.h"
#include"include/levels/level3.h"
#include"include/levels/level4.h"
#include"include/levels/title_screen.h"

#include"../engine/include/game_systems.h"

void Game::init()
{
	// Register levels
	Engine::Instance()->level_manager->registerLevel("level1", new Level1);
	Engine::Instance()->level_manager->registerLevel("level2", new Level2);
	Engine::Instance()->level_manager->registerLevel("level3", new Level3);
	Engine::Instance()->level_manager->registerLevel("level4", new Level4);
	Engine::Instance()->level_manager->registerLevel("menu", new TitleScreen);

	Engine::Instance()->sound_manager->setSFX_Volumes(Engine::Instance()->config_manager->config_values.at("sfx_levels"));

	// Set current level
	Engine::Instance()->level_manager->setCurrentLevel("level4");
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