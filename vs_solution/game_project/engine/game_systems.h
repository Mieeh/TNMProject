#pragma once

#include<graphics/renderers/batch_renderer.h>

#include"entity.h"

#include"engine.h"

/*
Master file for all game systems :
- rendering
- game state keeping
*/

class GraphicsSystem {
private:
	bear::graphics::BatchRenderer batch_renderer;

public:
	void init();
	void begin();
	void draw(Entity& entity);
	void flush();

	// Singleton, ignore
private:
	GraphicsSystem() { }
public:
	static GraphicsSystem* Instance();
};

class StateSystem {
public:
	GameState state;

	// Singleton, ignore
private:
	StateSystem() { }
public:
	static StateSystem* Instance();
};
