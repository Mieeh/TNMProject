#include "include/game_systems.h"

using namespace bear;

void GraphicsSingleton::init()
{
	batch_renderer.init();
}

void GraphicsSingleton::begin()
{
	batch_renderer.begin();
}

void GraphicsSingleton::draw(std::vector<Entity>& entity_list)
{
	for (auto &entity : entity_list) {
		batch_renderer.submit(&entity.renderable);
	}
}

void GraphicsSingleton::draw(Entity & entity)
{
	batch_renderer.submit(&entity.renderable);
}

void GraphicsSingleton::flush()
{
	batch_renderer.flush();
}

GraphicsSingleton * GraphicsSingleton::Instance()
{
	static GraphicsSingleton* instance = new GraphicsSingleton();
	return instance;
}

// Level Manager

void LevelManagerSingleton::registerLevel(const std::string & level_name, ILevel * level)
{
	level_map.insert(std::pair<std::string, ILevel*>(level_name, level));
}

void LevelManagerSingleton::setCurrentLevel(const std::string & level_name)
{
	current_level = level_map[level_name];
	current_level->init();
}

void LevelManagerSingleton::update_current_level(float dt)
{
	current_level->update(dt);
}

void LevelManagerSingleton::on_event_current_level(Event & event)
{
	current_level->on_event(event);
}

void LevelManagerSingleton::render_current_level()
{
	current_level->render();
}

LevelManagerSingleton * LevelManagerSingleton::Instance()
{
	static auto* instance = new LevelManagerSingleton();
	return instance;
}
