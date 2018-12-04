#pragma once

#include"entity.h"
#include<graphics/animated_sprite.h>

enum GATE_FACE_DIRECTION {
	FACING_RIGHT,
	FACING_LEFT,
	FACING_DOWN
};

enum GATE_STATE {
	LOCKED,
	UNLOCKING,
	UNLOCKED
};

struct Engine;

struct Gate {

	GATE_FACE_DIRECTION facing_direction;
	GATE_STATE gate_state;
	Entity entity;
	bear::graphics::AnimatedSprite unlock_animation;
	std::string last_frame_name;
	Engine* engine;

	Gate(GATE_FACE_DIRECTION _facing_direction);
	void unlock();
	void update(float dt);

};