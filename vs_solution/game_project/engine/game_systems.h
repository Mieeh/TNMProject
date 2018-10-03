#pragma once

#include<graphics/renderers/batch_renderer.h>

#include"entity.h"

/*
Master file for all game systems :
- rendering
*/

class Graphics {
private:
	bear::graphics::BatchRenderer batch_renderer;

public:
	void init();
	void begin();
	void draw(Entity& entity);
	void flush();

	// Singleton, ignore
private:
	Graphics() { }
public:
	static Graphics* Instance();
};
