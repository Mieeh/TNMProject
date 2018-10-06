#pragma once

#include"../../engine/include/level_interface.h"

struct MenuLevel : ILevel {

	Entity someBitch;

	void init() override
	{
		someBitch.renderable.m_Transform.m_Position = core::Vector2f(200, 200);
		someBitch.renderable.setTextureNameWData("topRightCorner");
	}

	void on_event(Event& event) override
	{
		if (event.type == EventType::KeyPressed) {
			if (event.key == Key::X) {
				LevelManagerSingleton::Instance()->setCurrentLevel("level1");
			}
		}
	}

	void update(float dt) override
	{
	}

	void render() override
	{
		GraphicsSingleton::Instance()->draw(someBitch);
	}
};