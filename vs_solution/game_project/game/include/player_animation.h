#pragma once

#include<graphics\animated_sprite.h>
using namespace bear;

struct PlayerAnimation {
	graphics::AnimatedSprite walk_right, walk_left, walk_up, walk_down;
	graphics::AnimatedSprite idle_animation;
	graphics::AnimatedSprite 

	PlayerAnimation();
	std::string update(int player_state, int move_direction, float dt);
};