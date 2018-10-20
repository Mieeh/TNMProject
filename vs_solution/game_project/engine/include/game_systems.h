#pragma once

#include<graphics/renderers/batch_renderer.h>
#include<graphics/view.h>
#include<window/event.h>

#include<map>
#include<string>

#include"bear_game.h"
#include"entity.h"
#include"level.h"
#include"engine.h"

/*
Master file for all game systems :
- rendering
- level managing
*/

using namespace bear;

class LevelManagerSingleton {

public:
	ILevel* current_level;
	std::map<std::string, ILevel*> level_map;

public:
	void registerLevel(const std::string& level_name, ILevel* level);
	void setCurrentLevel(const std::string& level_name);
	void reInitCurrentLevel();
	void update_current_level(float dt);
	void on_event_current_level(Event& event);
	void render_current_level();

	// Singleton, ignore
private:
	LevelManagerSingleton() { }
public:
	static LevelManagerSingleton* Instance();
};

class GraphicsSingleton {
private:
	bear::graphics::BatchRenderer batch_renderer;
	bear::graphics::BatchRenderer ui_renderer;

public:
	core::Vector2f window_size = core::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
	core::Vector2f* point_to_follow;
	graphics::View view;

public:
	void update(float dt);

	void init();
	void begin();
	void draw_as_ui(Entity& entity);
	void draw(std::vector<Entity>& entity_list);
	void draw(std::map<std::string, EnemyBase>& enemy_map);
	void draw(Entity& entity);
	void flush();

	void window_resized(const Event &event);

	// Singleton, ignore
private:
	GraphicsSingleton() { }
public:
	static GraphicsSingleton* Instance();
};
