#pragma once

#include<graphics\animated_sprite.h>
using namespace bear;

struct PlayerAnimation {
	graphics::AnimatedSprite walk_right, walk_left, walk_up, walk_down;
	graphics::AnimatedSprite idle_animation, idle_holding;
	graphics::AnimatedSprite walk_right_holding, walk_left_holding, walk_up_holding, walk_down_holding;
	graphics::AnimatedSprite death_animation;
	graphics::AnimatedSprite falling_animation;
	// Attack animations
	graphics::AnimatedSprite attack_right, attack_left, attack_down, attack_up;
	graphics::AnimatedSprite attack_right_sword, attack_left_sword, attack_down_sword, attack_up_sword;
	graphics::AnimatedSprite attack_right_item, attack_left_item, attack_down_item, attack_up_item;
	graphics::AnimatedSprite *current_attack_animation;

	const int attack_sword_speed = 5;
	const int attack_item_speed = 5;
	const int attack_speed = 5;

	PlayerAnimation();
	std::string update(int player_state, int move_direction, float dt);
	void play_attack(int direction);
	void stop_attack();
	void play_death();
	void stop_death();
};