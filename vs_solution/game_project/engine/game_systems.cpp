#include "game_systems.h"

void Graphics::init()
{
	batch_renderer.init();
}

void Graphics::begin()
{
	batch_renderer.begin();
}

void Graphics::draw(Entity & entity)
{
	batch_renderer.submit(&entity.renderable);
}

void Graphics::flush()
{
	batch_renderer.flush();
}

Graphics * Graphics::Instance()
{
	static Graphics* instance = new Graphics();
	return instance;
}
