#include "include/game_systems.h"

using namespace bear;

#include<fstream> // Used for loading configs
#include<math.h>

#include<core/vector2.h>

#include<graphics\graphics.h>
#include<window\GLFW_event.h>
#include<memory\resource_manager.h>

void GraphicsManager::init()
{
	// Create and init renderers
	slow_renderer = new bear::graphics::SlowRenderer();
	slow_ui_renderer = new bear::graphics::SlowRenderer();
	slow_renderer->init();
	slow_ui_renderer->init();
	
	graphics::Shader* temp_shader = ResourceManager::Instance()->CreateShaderFromFile("framebuffer_shader", "resources\\fb_vertex.txt", "resources\\fb_fragment.txt", "");
	framebuffer_list[0].setShader("framebuffer_shader");
}

GraphicsManager::~GraphicsManager()
{
	//std::cout << "Graphics Singleton exit called\n";
	delete slow_renderer;
	delete slow_ui_renderer;
}

void GraphicsManager::update(float dt) {

	// Make the view follow the point_to_follow
	if (point_to_follow != nullptr) {
		core::Vector2f goal_pos = ((*point_to_follow) * -1) + core::Vector2f((window_size.x/2) - TILE_SIZE/2, (window_size.y/2) - TILE_SIZE/2);
		core::Vector2f curr = view.getPosition();
		if (core::Vector2f::distance(curr, goal_pos) > 1.0f) {
			curr.lerp(goal_pos, 0.0025f*dt);
			curr.x = round(curr.x);
			curr.y = round(curr.y);
			view.setPosition(curr);
		}
	}
}

void GraphicsManager::set_post_processing_effect(POST_PROCESSING_EFFECTS _v)
{
	if (_v == POST_PROCESSING_EFFECTS::NONE) {
		slow_renderer->setFramebuffer(nullptr);
		framebuffer_list[0].unbind();
	}
	else {
		slow_renderer->setFramebuffer(&framebuffer_list[static_cast<int>(_v)]);
	}
}

void GraphicsManager::begin()
{
	slow_renderer->begin();
	slow_ui_renderer->begin();
}

void GraphicsManager::draw_as_ui(Entity & entity)
{
	slow_ui_renderer->submit(entity.renderable);
}

void GraphicsManager::draw(std::vector<Entity>& entity_list)
{
	for (auto &entity : entity_list) {
		slow_renderer->submit(entity.renderable);
	}
}

void GraphicsManager::draw(std::map<std::string, EnemyBase>& enemy_map)
{
	for (auto& x : enemy_map) {
		if (!x.second.is_dead)
			slow_renderer->submit(x.second.entity.renderable);
	}
}

void GraphicsManager::draw(std::map<std::string, Item>& item_map) {
	for (auto& x : item_map) {
		if(x.second.state == ItemState::ON_MAP)
			slow_renderer->submit(x.second.entity.renderable);
	}
}

void GraphicsManager::draw(Entity & entity)
{
	slow_renderer->submit(entity.renderable);
}

void GraphicsManager::flush()
{
	slow_renderer->flush(view);
	graphics::Framebuffer::FBOunbind();
	slow_ui_renderer->flush();
}

//std::cout << "Level Manager exit called!\n";
void GraphicsManager::window_resized(const Event & event)
{
	if (event.type == EventType::WindowReiszed) {
		// Bear framework callback for the rendering
		graphics::Graphics::window_resize_callback(event.size.x, event.size.y);
		window_size = event.size;

		// Notes(david) framebuffer needs to know the window was resized!
		//framebuffer->windowResize()
	}
}

// Level Manager

LevelManager::~LevelManager()
{
	current_level = nullptr;
	auto it = std::map<std::string, ILevel*>::iterator();
	for (it = level_map.begin() ; it != level_map.end() ; ) {
		delete it->second;
		it = level_map.erase(it);
	}
}

void LevelManager::registerLevel(const std::string & level_name, ILevel * level)
{
	level_map.insert(std::pair<std::string, ILevel*>(level_name, level));
}

void LevelManager::setCurrentLevel(const std::string & level_name)
{
	if (level_map.find(level_name) != level_map.end()) {
		current_level = level_map[level_name];
		current_level->init();
	}
	else {
		std::cout << "ERROR: Big fucking error; trying to load an non-existing level" << std::endl;
	}
}

void LevelManager::reInitCurrentLevel()
{
	current_level->init();
}

void LevelManager::update_current_level(float dt)
{
	current_level->update(dt);
}

void LevelManager::on_event_current_level(Event & event)
{
	current_level->on_event(event);
}

void LevelManager::render_current_level()
{
	current_level->render();
}

// Config manager

void ConfigManager::load_key_bindings()
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

void ConfigManager::load_config_values()
{
	std::string path = RESOURCES_RELATIVE_PATH + std::string("config.txt");
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cout << "Big fucking ERROR! Can't load configuration file" << std::endl;
	}

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	file.close(); // Close the file, we're done with it

	// Go through each line from the config file and register the value in the map
	for (auto line : lines) {
		int split_index = line.find(" ");
		std::string key = line.substr(0, split_index);
		std::string value = line.substr(split_index + 1, line.length() - split_index + 1);
		auto converted = std::stof(value);
		
		config_values.insert(std::pair<std::string, float>(key, converted));
	}
}

// Music manager

void SoundManager::update(float dt)
{
	for (auto i = 0; i < sfx_poll.size(); i++) {
		// get delayed sfx and increment timer
		DelayedSFX& delayed_sfx = sfx_poll.at(i);
		delayed_sfx.timer += 1 * dt;

		// Pop the delayed sfx?
		if (delayed_sfx.timer >= delayed_sfx.delay) {
			sfx_list.at(delayed_sfx.name)->sf_sound.play();
			sfx_poll.erase(sfx_poll.begin() + i);
			continue;
		}
	}
}

SoundManager::~SoundManager()
{
	//for (const auto& x : music_list) {
	//	music_list.erase(x.first);
	//}
	//for (const auto& x : sfx_list) {
	//	sfx_list.erase(x.first);
	//}
}

void SoundManager::register_music(std::string name, const std::string & path)
{
	music_list.insert(std::pair<std::string, std::shared_ptr<Music>>(name, std::make_shared<Music>(path)));
}

std::shared_ptr<Music> SoundManager::get_music(std::string name)
{
	return music_list.at(name);
}

void SoundManager::register_sfx(std::string name, const std::string & path)
{
	sfx_list.insert(std::pair<std::string, std::shared_ptr<SFX>>(name, std::make_shared<SFX>(path)));
}

std::shared_ptr<SFX> SoundManager::get_sfx(std::string name)
{
	return sfx_list.at(name);
}

void SoundManager::add_delayed_sfx(std::string name, float delay)
{
	DelayedSFX delayed_sfx;
	delayed_sfx.name = name;
	delayed_sfx.timer = 0;
	delayed_sfx.delay = delay;
	sfx_poll.emplace_back(delayed_sfx);
}

void SoundManager::setSFX_Volumes(float volume)
{
	for (auto it = sfx_list.begin(); it != sfx_list.end(); ++it) {
		it->second->sf_sound.setVolume(volume);
	}
}
