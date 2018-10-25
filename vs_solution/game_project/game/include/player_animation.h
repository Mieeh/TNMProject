#pragma once

#include<graphics\animated_sprite.h>
using namespace bear;

struct PlayerAnimation {
	graphics::AnimatedSprite walk_right, walk_left, walk_up, walk_down;

	PlayerAnimation();
	std::string update(int player_state, int move_direction, float dt);
};