#include"bear_game.h"
#include"constants.h"

using namespace bear;
using namespace bear::window;

Engine::Engine(BearClass* bear_class)
{
	// Create some framework related objects
	game_window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "TNM Project");
	game_window->setVSync(VSYNC);

	// Call "game" init
	this->bear_class = bear_class;
	bear_class->init();

	// Go into the main loop
	this->core();
}

Engine::~Engine()
{
	// Delete some framework related objects
	delete game_window;

	bear_class->exit();
}

void Engine::core()
{
	while (game_window->isOpen()) {
		// Event polling
		for (Event event : game_window->getRegisteredEvents()) {

			if (event.type == EventType::Closed) {
				game_window->close(); // Close the window
			}

			// Send events to game
			bear_class->on_event(event);
		}

		// rendering
		game_window->clear();

		game_window->display();
	}
}