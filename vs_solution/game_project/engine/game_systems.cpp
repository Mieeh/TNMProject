#include "game_systems.h"

using namespace bear;

void GraphicsSystem::init()
{
	batch_renderer.init();
}

void GraphicsSystem::begin()
{
	batch_renderer.begin();
}

void GraphicsSystem::draw(Entity & entity)
{
	batch_renderer.submit(&entity.renderable);
}

void GraphicsSystem::flush()
{
	batch_renderer.flush();
}

GraphicsSystem * GraphicsSystem::Instance()
{
	static GraphicsSystem* instance = new GraphicsSystem();
	return instance;
}

// State System

StateSystem * StateSystem::Instance()
{
	static auto* instance = new StateSystem();
	return instance;
}
