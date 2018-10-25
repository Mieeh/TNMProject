#include"include/player_animation.h"

#include"include/player.h"

PlayerAnimation::PlayerAnimation() {

	for (int i = 1; i <= 8; i++) {
		graphics::AnimatedKeyframe running_down = { "runningDown" + std::to_string(i) };
		graphics::AnimatedKeyframe running_left = { "runningLeft" + std::to_string(i) };
		graphics::AnimatedKeyframe running_right = { "runningRight" + std::to_string(i) };
		graphics::AnimatedKeyframe running_up = { "runningUp" + std::to_string(i) };

		walk_down.addKeyframe(running_down);
		walk_left.addKeyframe(running_left);
		walk_right.addKeyframe(running_right);
		walk_up.addKeyframe(running_up);
	}

	walk_up.m_IsLooping = true;
	walk_right.m_IsLooping = true;
	walk_down.m_IsLooping = true;
	walk_left.m_IsLooping = true;

	walk_up.m_TickBreak = 100;
	walk_right.m_TickBreak = 10;
	walk_down.m_TickBreak = 100;
	walk_left.m_TickBreak = 100;

	walk_right.play();
}

std::string PlayerAnimation::update(int player_state, int move_direction, float dt) {

	walk_right.update(dt);
	return walk_right.m_CurrentTextureName;

	/*
	if (player_state == PlayerStates::IN_TRANSIT) {
		switch (move_direction) {
		case PlayerMoveDirection::LEFT:
			walk_left.update(dt);
			current_animation = walk_left;
			break;
		case PlayerMoveDirection::RIGHT:
			walk_right.update(dt);
			current_animation = walk_right;
			break;		
		case PlayerMoveDirection::DOWN:
			walk_down.update(dt);
			current_animation = walk_down;
			break;		
		case PlayerMoveDirection::UP:
			walk_up.update(dt);
			current_animation = walk_up;
			break;
		}
		
	}
	*/
}