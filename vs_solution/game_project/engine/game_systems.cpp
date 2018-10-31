#include "include/game_systems.h"

using namespace bear;

#include<fstream> // Used for loading configs
#include<math.h>

#include<core/vector2.h>

void GraphicsSingleton::init()
{
	// Create and init renderers
	slow_renderer = new bear::graphics::SlowRenderer();
	slow_ui_renderer = new bear::graphics::SlowRenderer();
	slow_renderer->init();
	slow_ui_renderer->init();
}

void GraphicsSingleton::exit()
{
	//std::cout << "Graphics Singleton exit called\n";
	delete slow_renderer;
	delete slow_ui_renderer;
}

void GraphicsSingleton::update(float dt) {

	// Make the view follow the point_to_follow
	if (point_to_follow != nullptr) {
		core::Vector2f goal_pos = ((*point_to_follow) * -1) + core::Vector2f((window_size.x/2) - TILE_SIZE/2, (window_size.y/2) - TILE_SIZE/2);
		core::Vector2f curr = view.getPosition();
		if (core::Vector2f::distance(curr, goal_pos) > 1.0f) {
			curr.lerp(goal_pos, 0.0025f*dt);
			//curr.moveTowards(goal_pos, 0.1f*dt);
			curr.x = round(curr.x);
			curr.y = round(curr.y);
			view.setPosition(curr);
		}
	}
}

void GraphicsSingleton::begin()
{
	slow_renderer->begin();
	slow_ui_renderer->begin();
}

void GraphicsSingleton::draw_as_ui(Entity & entity)
{
	slow_ui_renderer->submit(entity.renderable);
}

void GraphicsSingleton::draw(std::vector<Entity>& entity_list)
{
	for (auto &entity : entity_list) {
		slow_renderer->submit(entity.renderable);
	}
}

void GraphicsSingleton::draw(std::map<std::string, EnemyBase>& enemy_map)
{
	for (auto& x : enemy_map) {
		if (!x.second.is_dead)
			slow_renderer->submit(x.second.entity.renderable);
	}
}

void GraphicsSingleton::draw(Entity & entity)
{
	slow_renderer->submit(entity.renderable);
}

void GraphicsSingleton::flush()
{
	slow_renderer->flush(view);
	slow_ui_renderer->flush();
}

void GraphicsSingleton::window_resized(const Event & event)
{
	if (event.type == EventType::WindowReiszed) {
		// Bear framework callback for the rendering
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

void LevelManagerSingleton::exit()
{
	//std::cout << "Level Manager exit called!\n";

	current_level = nullptr;
	auto it = std::map<std::string, ILevel*>::iterator();
	for (it = level_map.begin(); it != level_map.end(); ++it) {
		delete it->second;
		level_map.erase(it);
	}
}

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

// Config singleton
void ConfigSingleton::load_key_bindings()
{
	std::string path = RESOURCES_RELATIVE_PATH + std::string("keybindings.txt");
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cout << "Big fucking ERROR! Can't load keybindings configfile" << std::endl;
	}

	std::vector<std::string> file_lines;
	std::string line;
	while (file >> line) {
		file_lines.push_back(line);
	}

	file.close(); // Close the file, we're done with it

	// Go through each line from the kydbindings config file and register them to the keymap
	for (std::string line : file_lines) {
		int split_index = line.find(":");
		std::string key = line.substr(0, split_index);
		int value = std::stoi(line.substr(split_index + 1, line.length() - split_index + 1));
		// Register to keymap
		key_map.insert(std::pair<std::string, Key>(key, static_cast<Key>(value)));
	}
}

ConfigSingleton * ConfigSingleton::Instance()
{
	static auto* instance = new ConfigSingleton();
	return instance;
}

// Music singleton

SoundSingleton* SoundSingleton::instance = nullptr;

void SoundSingleton::exit()
{
	//std::cout << "Sound Singleton exit called\n";

	for (const auto& x : music_list) {
		music_list.erase(x.first);
	}
	for (const auto& x : sfx_list) {
		sfx_list.erase(x.first);
	}
}

void SoundSingleton::register_music(std::string name, const std::string & path)
{
	music_list.insert(std::pair<std::string, std::shared_ptr<Music>>(name, std::make_shared<Music>(path)));
}

std::shared_ptr<Music> SoundSingleton::get_music(std::string name)
{
	return music_list.at(name);
}

void SoundSingleton::register_sfx(std::string name, const std::string & path)
{
	sfx_list.insert(std::pair<std::string, std::shared_ptr<SFX>>(name, std::make_shared<SFX>(path)));
}

std::shared_ptr<SFX> SoundSingleton::get_sfx(std::string name)
{
	return sfx_list.at(name);
}

SoundSingleton * SoundSingleton::Instance()
{
	if (instance == nullptr)
		instance = new SoundSingleton();
	return instance;
}
