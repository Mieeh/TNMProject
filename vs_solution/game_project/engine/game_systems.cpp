#include "include/game_systems.h"

using namespace bear;

void GraphicsSingleton::init()
{
	batch_renderer.init();
	ui_renderer.init();
}

void GraphicsSingleton::update(float dt) {

	// Make the view follow the point_to_follow
	if (point_to_follow != nullptr) {
		core::Vector2f goal_pos = ((*point_to_follow) * -1) + core::Vector2f((window_size.x/2) - TILE_SIZE/2, (window_size.y/2) - TILE_SIZE/2);
		core::Vector2f curr = view.getPosition();
		if (core::Vector2f::distance(curr, goal_pos) > 2.0f) {
			curr.lerp(goal_pos, 0.0025f*dt);
			view.setPosition(curr);
		}
	}
}

void GraphicsSingleton::begin()
{
	ui_renderer.begin();
	batch_renderer.begin();
}

void GraphicsSingleton::draw_as_ui(Entity & entity)
{
	ui_renderer.submit(&entity.renderable);
}

void GraphicsSingleton::draw(std::vector<Entity>& entity_list)
{
	for (auto &entity : entity_list) {
		batch_renderer.submit(&entity.renderable);
	}
}

void GraphicsSingleton::draw(std::map<std::string, EnemyBase>& enemy_map)
{
	for (auto& x : enemy_map) {
		if(!x.second.is_dead)
			batch_renderer.submit(&x.second.entity.renderable);
	}
}

void GraphicsSingleton::draw(Entity & entity)
{
	batch_renderer.submit(&entity.renderable);
}

void GraphicsSingleton::flush()
{
	batch_renderer.flush(view);
	ui_renderer.flush();
}

void GraphicsSingleton::window_resized(const Event & event)
{
	if (event.type == EventType::WindowReiszed) {
		// Do the stuff neccesary 
		graphics::Graphics::window_resize_callback(event.size.x, event.size.y);
		window_size = event.size;
	}
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
	if (level_map.find(level_name) != level_map.end()) {
		current_level = level_map[level_name];
		current_level->init();
	}
	else {
		std::cout << "ERROR: Big fucking error; trying to load an non-existing level" << std::endl;
	}
}

void LevelManagerSingleton::reInitCurrentLevel()
{
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
