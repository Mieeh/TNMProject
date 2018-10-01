#pragma once

#include"bear_framework.h"

/* This class gets inherited by the main "game" class
* 1. put all core-framework code here!
*/

struct BearClass {
	// Implemented by the "game"
	virtual void init() { }
	virtual void update(float dt) { }
	virtual void on_event(bear::Event& event) { }
	virtual void exit() { }
};

// Game creates one of these!

struct Engine {
	BearClass *bear_class;
	bear::window::Window* game_window;
	bear::graphics::BatchRenderer* main_renderer;

	Engine(BearClass* bear_class);
	~Engine();

	// Ran here
	void core();
};
