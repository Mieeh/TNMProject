#pragma once

#include"bear_framework.h"

/* This class gets inherited by the main "game" class
* 1. put all core-framework code here!
*/

struct BearClass {
	// Implemented by the "game"
	virtual void init() { }
	virtual void update(float dt) { }
	virtual void render() { }
	virtual void on_event(bear::Event& event) { }
	virtual void exit() { }
};

// Game creates one of these!

struct Engine {
	static Engine* instance;
	BearClass *bear_class;
	bear::window::Window* game_window;
	bear::graphics::BatchRenderer* main_renderer;

	// Cam shake stuff
	bool do_window_shake = false;
	bear::core::Vector2i origin;
	float counter, length, intensity;

	Engine(BearClass* bear_class);
	~Engine();

	void perform_window_shake(float length, float intensity);
	// Internal stuff
	void update(float dt);
	// Creates all the resources using the bear::ResourceManager
	void loadResources();
	// Main game loop
	void core();
};
