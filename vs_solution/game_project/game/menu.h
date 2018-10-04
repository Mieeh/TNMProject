#pragma once

#include<memory\resource_manager.h>
#include<window\event.h>
using namespace bear;

#include"../engine/space.h"
#include"../engine/game_systems.h"

struct Menu {

	Space menu_space;
	StateSystem* state_system = StateSystem::Instance();

	Menu() : menu_space()
	{
		ResourceManager::Instance()->CreateTexture("menu", "resources\\menu.png", graphics::image_format::RGB);
		
		auto temp = menu_space.addEntity("background_entity");
		temp->renderable.setTextureNameWData("menu");
	}

	void update(float dt) {

	}

	void on_event(Event& event) {
		if (event.type == EventType::KeyPressed) { 
			if (event.key == Key::X) {
				StateSystem::Instance()->state = GameState::PLAYING;
			}
		}
	}

	void render()
	{
		GraphicsSystem::Instance()->draw(*menu_space.getEntity("background_entity"));
	}

};