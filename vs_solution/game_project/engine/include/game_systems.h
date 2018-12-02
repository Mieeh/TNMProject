#pragma once

#include<graphics/renderers/slow_renderer.h>
#include<graphics\renderers\particle_source.h>
//#include<graphics/renderers/batch_renderer.h>
#include<graphics/view.h>
#include<window/event.h>
#include<window\GLFW_event.h>
#include<graphics\framebuffer.h> // Post processing 

#include<map>
#include<string>
#include<memory>

#include"entity.h"
#include"level.h"
#include"engine.h"
#include"sfml_audio_wrapper.h"
#include"item.h"

using namespace bear;

class LevelManager {

public:
	ILevel* current_level;
	std::map<std::string, ILevel*> level_map;

public:
	LevelManager() { }
	~LevelManager();

	void registerLevel(const std::string& level_name, ILevel* level);
	void setCurrentLevel(const std::string& level_name);
	void reInitCurrentLevel();
	void update_current_level(float dt);
	void on_event_current_level(Event& event);
	void render_current_level();
};

enum POST_PROCESSING_EFFECTS {
	NONE = -1,
	BLACK_WHITE_CROSS = 0
};

class GraphicsManager {
private:
	// Bear framework rendering objects 
	bear::graphics::SlowRenderer *slow_renderer;
	bear::graphics::SlowRenderer *slow_ui_renderer;

public:									
	bear::graphics::ParticleSource *particle_source;
	core::Vector2f window_size = core::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
	core::Vector2f* point_to_follow;
	graphics::View view;
	graphics::Framebuffer framebuffer_list[1] = { graphics::Framebuffer(WINDOW_WIDTH, WINDOW_HEIGHT) }; // Number of entries in the post processing enum

public:
	GraphicsManager() { }
	~GraphicsManager();

	void update(float dt);

	void set_post_processing_effect(POST_PROCESSING_EFFECTS _v);

	void init();

	void begin();
	void draw_as_ui(Entity& entity);
	void draw(std::vector<Entity>& entity_list);
	void draw(std::map<std::string, EnemyBase>& enemy_map);
	void draw(std::map<std::string, Item>& item_map);
	void draw(std::map<std::string, PresurePlate>& pp_map);
	void draw(Entity& entity);
	void flush();

	void window_resized(const Event &event);
};

class ConfigManager {
public:
	std::map<std::string, Key> key_map;
	std::map<std::string, float> config_values;
	
public:
	ConfigManager() { }

	void load_key_bindings();
	void load_config_values();
};

class SoundManager {

private:
	std::map<std::string, std::shared_ptr<Music>> music_list;
	std::map<std::string, std::shared_ptr<SFX>> sfx_list;

	struct DelayedSFX {
		float timer;
		float delay;
		std::string name;
	};

	std::vector<DelayedSFX> sfx_poll;
	std::string background_music;

public:
	SoundManager() { }
	~SoundManager();

	void update(float dt);
	
	void set_background_music(const std::string& new_background_music);
	void start_background_music();
	void stop_background_music();

	void register_music(std::string name, const std::string& path);
	std::shared_ptr<Music> get_music(std::string name);
	void register_sfx(std::string name, const std::string& path);
	std::shared_ptr<SFX> get_sfx(std::string name);
	void add_delayed_sfx(std::string name, float delay);

	void setSFX_Volumes(float volume);
};
