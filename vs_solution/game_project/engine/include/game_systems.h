#pragma once

#include<graphics/renderers/batch_renderer.h>
#include<graphics/view.h>
#include<window/event.h>

#include<map>
#include<string>
#include<memory.h>

#include"bear_game.h"
#include"entity.h"
#include"level.h"
#include"engine.h"
#include"sfml_audio_wrapper.h"

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

class ConfigSingleton {
public:
	void load_key_bindings();

	std::map<std::string, Key> key_map;

	// Singleton, ignore
private:
	ConfigSingleton() { }
public:
	static ConfigSingleton* Instance();

};

class SoundSingleton {

private:
	std::map<std::string, std::shared_ptr<Music>> music_list;
	std::map<std::string, std::shared_ptr<SFX>> sfx_list;

public:
	void register_music(std::string name, const std::string& path);
	std::shared_ptr<Music> get_music(std::string name);
	void register_sfx(std::string name, const std::string& path);
	std::shared_ptr<SFX> get_sfx(std::string name);

	// Singleton, ignore
private:
	SoundSingleton() { }
	static SoundSingleton* instance;

public:
	static SoundSingleton* Instance();
};
