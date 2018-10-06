#pragma once

#include"../../engine/level/level_interface.h"

struct MenuLevel : ILevel {

	float t = 0;
	core::Vector2f o;
	Entity someBitch;

	void init() override
	{
		someBitch.renderable.m_Color = core::Color::Red();
		someBitch.renderable.m_Transform.m_Size = core::Vector2f(50, 150);
		someBitch.renderable.m_Transform.m_Position = core::Vector2f(200, 200);
		o = someBitch.renderable.m_Transform.m_Position;
		t = 0;
		std::cout << "menu init!\n";
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
		t += 1;
		someBitch.renderable.m_Transform.m_Size = o + core::Vector2f(50*sin(0.1f*t), 0);
	}

	void render() override
	{
		GraphicsSingleton::Instance()->draw(someBitch);
	}
};