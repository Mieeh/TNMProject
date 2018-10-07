#pragma once

#include"../../engine/include/entity.h"
#include<window\event.h>
#include<core\vector2.h>

using namespace bear;

class Player {

private:
	Entity entity;

public:
	core::Vector2i position;

	void on_event(Event& event);
	void update(float dt);
	void render();

public:
	static Player* get();
private:
	Player();
	static Player* instance;
};