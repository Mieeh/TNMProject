#pragma once

#include"entity.h"
#include<graphics/animated_sprite.h>

enum GATE_FACE_DIRECTION {
	FACING_RIGHT,
	FACING_LEFT,
	FACING_DOWN,
	FACING_UP
};

enum GATE_STATE {
	LOCKED,
	UNLOCKING,
	UNLOCKED
};

enum GATE_TYPE {
	NORMAL,
	RED
};

struct Engine;

struct Gate {

	GATE_TYPE gate_type;
	GATE_FACE_DIRECTION facing_direction;
	GATE_STATE gate_state;
	Entity entity;
	bear::graphics::AnimatedSprite unlock_animation;
	std::string last_frame_name;
	Engine* engine;

	Gate(GATE_FACE_DIRECTION _facing_direction, GATE_TYPE _gate_type);
	void unlock();
	void update(float dt);

};