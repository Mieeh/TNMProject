#include"include/bear_game.h"
#include"include/engine.h"

#include"include/game_systems.h"

#include<graphics/graphics.h>
#include<memory\resource_manager.h>
#include<core\file_utility.h>

#include<filesystem>

namespace fs = std::experimental::filesystem;

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

	// Load resources
	this->loadResources();

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

void Engine::loadResources()
{
	static bool call_flag = false;
	if (call_flag) {
		std::cout << "EREOR: Trying to load game resources twice or more! Not good!\n";
	}

	// Loop through each .png file int the /resources folder and register the texture with filename as name
	std::vector<std::string> paths;
	// 1. Get all .png paths
	for (auto &path : fs::directory_iterator(RESOURCES_RELATIVE_PATH)) {
		std::string p = path.path().string();
		if (core::get_file_suffix(p) == ".png") {
			paths.push_back(p);
		}
	}
	for (auto &path : paths) {
		unsigned int i = path.find("\\"); // Name start ]
		unsigned int j = path.find("."); // Name end [
		std::string file_name = path.substr(i+1, (j-i)-1); 
		ResourceManager::Instance()->CreateTexture(file_name, path, graphics::image_format::RGBA);
	}

	call_flag = true;
}

void Engine::core()
{
	core::Clock dt_clock;
	dt_clock.start();
	float dt = 1.0f;

	while (game_window->isOpen()) {
		
		dt_clock.reset(); // Reset the clock for this frame

		// Event polling
		for (Event event : game_window->getRegisteredEvents()) {

			if (event.type == EventType::Closed) {
				game_window->close(); // Close the window
			}

			// Send events to game
			bear_class->on_event(event);
		}

		// call update
		bear_class->update(dt); 

		// rendering
		game_window->clear(UNLIT_BACKGROUND_COLOR);

		GraphicsSingleton::Instance()->begin();
		bear_class->render(); // Here is where the "game" submits the primitives to be rendered by the rendering system
		GraphicsSingleton::Instance()->flush();

		game_window->display();

		dt = dt_clock.getTicks(); // Get the number of ticks for this frame
	}

	bear_class->exit();
}