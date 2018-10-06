#include"bear_game.h"
#include"engine.h"

#include"game_systems.h"

#include<graphics/graphics.h>

using namespace bear;
using namespace bear::window;

Engine::Engine(BearClass* bear_class)
{
	// Create some framework related objects
	game_window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "TNM Project");
	game_window->setVSync(VSYNC);

	// Init bear-framework systems
	if (!bear::graphics::Graphics::init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
		std::cout << "ERROR: Failed to init BEAR-FRAMEWORK graphics!" << std::endl;
	}

	// Init game systems
	GraphicsSingleton::Instance()->init();

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

		// call update
		bear_class->update(1.0f); // Notes(david) add delta time for each frame!

		// rendering
		game_window->clear(UNLIT_BACKGROUND_COLOR);

		GraphicsSingleton::Instance()->begin();
		bear_class->render(); // Here is where the "game" submits the primitives to be rendered by the rendering system
		GraphicsSingleton::Instance()->flush();

		game_window->display();
	}

	bear_class->exit();
}