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

Engine* Engine::instance = nullptr;

Engine::Engine(BearClass* bear_class)
{
	Engine::instance = this;

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
	ConfigSingleton::Instance()->load_key_bindings();
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

void Engine::perform_window_shake(float length, float intensity)
{
	do_window_shake = true;
	this->length = length;
	this->intensity = intensity;
	counter = 0;
	this->origin = game_window->getWindowPosition();
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

	core::Clock fpsClock;
	fpsClock.start();
	size_t fps = 0;

	while (game_window->isOpen()) {
		
		if (fpsClock.getTicks() >= 1000) {
			std::cout << fps << std::endl;
			fps = 0;
			fpsClock.reset();
		}

		dt_clock.reset(); // Reset the clock for this frame

		// Event polling
		for (Event event : game_window->getRegisteredEvents()) {

			if (event.type == EventType::Closed) {
				game_window->close(); // Close the window
			}
			else if (event.type == EventType::WindowReiszed) {
				GraphicsSingleton::Instance()->window_resized(event);
			}

			// Send events to game
			bear_class->on_event(event);
		}

		// call update
		this->update(dt);
		bear_class->update(dt); 

		// rendering
		game_window->clear(UNLIT_BACKGROUND_COLOR);

		GraphicsSingleton::Instance()->begin();
		bear_class->render(); // Here is where the "game" submits the primitives to be rendered by the rendering system
		GraphicsSingleton::Instance()->flush();

		game_window->display();

		dt = dt_clock.getTicks(); // Get the number of ticks for this frame
		fps++;
	}

	bear_class->exit();
}

void Engine::update(float dt)
{
	static float constant = 1.5f;

	if (do_window_shake) {
		counter += 1.5f * dt;
		if (counter < length) {
			// Perform "window" shake
			core::Vector2i pos = game_window->getWindowPosition();
			core::Vector2i new_pos = pos + (core::Vector2i)core::randomPointInsideCircle(intensity);
			game_window->setWindowPosition(new_pos);
		}
		else {
			do_window_shake = false;
			game_window->setWindowPosition(origin);
		}
	}
}


