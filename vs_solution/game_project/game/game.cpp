#include"include/game.h"

#include"include/levels/level1.h"
#include"include/levels/level2.h"
#include"include/levels/menu.h"

#include"../engine/include/game_systems.h"

void Game::init()
{
	// Register levels
	engine->level_manager->registerLevel("level1", new Level1);
	engine->level_manager->registerLevel("level2", new Level2);
	engine->level_manager->registerLevel("menu", new TitleScreen);

	engine->sound_manager->get_music("bg")->sf_music.play();

	// Set current level
	engine->level_manager->setCurrentLevel("menu");
}

void Game::update(float dt) {
	engine->graphics_manager->update(dt);
	engine->level_manager->update_current_level(dt);
}

void Game::render() {
	engine->level_manager->render_current_level();
}

void Game::on_event(Event& event) {
	engine->level_manager->on_event_current_level(event);
}

void Game::exit()
{

}