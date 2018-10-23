#include"include/game.h"

#include"include/levels/level1.h"
#include"include/levels/level2.h"
#include"include/levels/menu.h"

void Game::init()
{
	// Register levels
	level_manager->registerLevel("level1", new Level1);
	level_manager->registerLevel("level2", new Level2);
	level_manager->registerLevel("menu", new TitleScreen);

	// Set current level
	level_manager->setCurrentLevel("menu");
}

void Game::update(float dt) {
	graphics_singleton->update(dt);
	level_manager->update_current_level(dt);
}

void Game::render() {
	level_manager->render_current_level();
}

void Game::on_event(Event& event) {
	level_manager->on_event_current_level(event);
}

void Game::exit()
{

}