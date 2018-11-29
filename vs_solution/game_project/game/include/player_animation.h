#pragma once

#include<graphics\animated_sprite.h>
using namespace bear;

struct PlayerAnimation {
	graphics::AnimatedSprite walk_right, walk_left, walk_up, walk_down;
	graphics::AnimatedSprite idle_animation, idle_holding;
	graphics::AnimatedSprite walk_right_holding, walk_left_holding, walk_up_holding, walk_down_holding;

	PlayerAnimation();
	std::string update(int player_state, int move_direction, float dt);
};