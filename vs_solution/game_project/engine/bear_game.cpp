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

Engine::~Engine()
{
	
}

Engine * Engine::Instance()
{
	if (instance == nullptr) {
		instance = new Engine();
	}
	return instance;
}

void Engine::init(BearClass* bear_class)
{
	this->bear_class = bear_class;

	// Do this absolute first 
	config_manager = std::make_unique<ConfigManager>();
	config_manager->load_config_values();

	// Create some framework related objects
	game_window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "TNM Project", config_manager->config_values.at("fullscreen"));
	game_window->setVSync(VSYNC);

	// Init bear-framework systems
	if (!bear::graphics::Graphics::init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
		std::cout << "ERROR: Failed to init BEAR-FRAMEWORK graphics!" << std::endl;
	}

	//Create the game systems
	level_manager = std::make_unique<LevelManager>();
	graphics_manager = std::make_unique<GraphicsManager>();
	sound_manager = std::make_unique<SoundManager>();

	config_manager->load_key_bindings();
	graphics_manager->init();

	// Load resources
	this->loadResources();

	this->core();
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
		return;
	}

	// Loop through each .png file in the /resources folder and register the texture with filename as name
	std::vector<std::string> image_paths;
	// Get all png(rgba) paths
	for (auto &path : fs::directory_iterator(PNG_RELATIVE_PATH)) {
		image_paths.push_back(path.path().string());
	}
	// Load pngs
	for (auto &path : image_paths) {
		unsigned int i = path.find_last_of("\\"); // Name start ]
		unsigned int j = path.find("."); // Name end [
		std::string file_name = path.substr(i+1, (j-i)-1);
		ResourceManager::Instance()->CreateTexture(file_name, path, graphics::image_format::RGBA);
	}

	// Get all jpg(rgb) paths
	image_paths.clear();
	for (auto &path : fs::directory_iterator(JPG_RELATIVE_PATH)) {
		image_paths.push_back(path.path().string());
	}
	// Load them
	for (auto& path : image_paths) {
		unsigned int i = path.find_last_of("\\"); // Name start ]
		unsigned int j = path.find("."); // Name end [
		std::string file_name = path.substr(i + 1, (j - i) - 1);
		ResourceManager::Instance()->CreateTexture(file_name, path, graphics::image_format::RGB);
	}

	// Loop through each .ogg file in the /resources/music and register them with the filename as name
	std::vector<std::string> music_paths;
	// 2. Get all .ogg music files
	for (auto &path : fs::directory_iterator(MUSIC_RELATIVE_PATH)) {
		std::string p = path.path().string();
		if (core::get_file_suffix(p) == ".ogg") {
			music_paths.push_back(p);
		}
	}
	for (auto &path : music_paths) {
		unsigned int i = path.find_last_of("\\"); // Name start ]
		unsigned int j = path.find("."); // Name end [
		std::string file_name = path.substr(i + 1, (j - i) - 1);
		sound_manager->register_music(file_name, path);
	}

	// Loop through each .ogg file in the /resources/sfx and register them with the same fucking name as filename
	std::vector<std::string> sfx_paths;
	for (auto &path : fs::directory_iterator(SFX_RELATIVE_PATH)) {
		std::string p = path.path().string();
		if (core::get_file_suffix(p) == ".ogg" || core::get_file_suffix(p) == ".wav") {
			sfx_paths.push_back(p);
		}
	}
	for (auto & path : sfx_paths) {
		unsigned int i = path.find_last_of("\\"); // Name start ]
		unsigned int j = path.find("."); // Name end [
		std::string file_name = path.substr(i + 1, (j - i) - 1);
		sound_manager->register_sfx(file_name, path);
	}

	call_flag = true;
}

void Engine::core()
{
	// Call "game" init
	bear_class->init();

	core::Clock dt_clock;
	dt_clock.start();
	float dt = 1.0f;

	core::Clock fpsClock;
	fpsClock.start();
	size_t fps = 0;

	while (game_window->isOpen()) {
		
		if (fpsClock.getTicks() >= 1000) {
			//std::cout << fps << std::endl;
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
				graphics_manager->window_resized(event);
			}

			// Send events to game
			bear_class->on_event(event);
		}

		// call update
		this->update(dt);
		bear_class->update(dt); 
		sound_manager->update(dt);

		// rendering
		game_window->clear(UNLIT_BACKGROUND_COLOR);

		graphics_manager->begin();
		bear_class->render(); // Here is where the "game" submits the primitives to be rendered by the rendering system
		graphics_manager->flush();

		game_window->display();

		dt = dt_clock.getTicks(); // Get the number of ticks for this frame
		fps++;
	}

	exit();
}

void Engine::exit()
{
	bear_class->exit();

	delete game_window;
	
	delete instance;
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


