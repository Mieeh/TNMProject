#include"game.h"

void Game::init()
{
	menu = new Menu();
	state_system->state = GameState::MENU;
}

void Game::update(float dt) {
	switch (state_system->state) {
		case GameState::MENU:
			// Run menu!
			menu->update(dt);
			break;
		case GameState::PLAYING:
			// Run game!
			break;
		default:
			// Something is very wrong here!
			break;
	}
}

void Game::render() {
	switch (state_system->state) {
	case GameState::MENU:
		// Render menu
		menu->render();
		break;
	case GameState::PLAYING:
		// Render game
		break;
	default:
		// Something is very wrong here!
		break;
	}
}

void Game::on_event(Event& event) {
	switch (state_system->state) {
	case GameState::MENU:
		// Send event to menu!
		menu->on_event(event);
		break;
	case GameState::PLAYING:
		// Send events to menu!
		break;
	default:
		// Something is very wrong here!
		break;
	}
}

void Game::exit()
{
	delete menu;
}