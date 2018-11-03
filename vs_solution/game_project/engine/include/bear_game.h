#pragma once

#include"bear_framework.h"
#include"game_systems.h"
 
/* This class gets inherited by the main "game" class */

struct BearClass {
	// Implemented by the "game"
	virtual void init() { }
	virtual void update(float dt) { }
	virtual void render() { }
	virtual void on_event(bear::Event& event) { }
	virtual void exit() { }
};

// Game creates one of these!

class Engine {
private:
	static Engine* instance;
	Engine() { }

public:
	static Engine* Instance();

	BearClass *bear_class;
	bear::window::Window* game_window;

	// Game systems
	LevelManager* level_manager;
	GraphicsManager* graphics_manager;
	ConfigManager* config_manager;
	SoundManager* sound_manager;
	
	// Cam shake stuff
	bool do_window_shake = false;
	bear::core::Vector2i origin;
	float counter, length, intensity;

	// Inits game
	void init(BearClass* bear_class);

	void perform_window_shake(float length, float intensity);
	// Internal stuff
	void update(float dt);
	// Creates all the resources using the bear::ResourceManager
	void loadResources();
	// Main game loop
	void core();
	// Called on application exit
	void exit();
};
