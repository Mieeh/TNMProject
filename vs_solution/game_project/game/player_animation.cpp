#include"include/player_animation.h"

#include"include/player.h"

PlayerAnimation::PlayerAnimation() {

	for (int i = 1; i <= 8; i++) {
		graphics::AnimatedKeyframe idle = { "idle1" };
		idle_animation.addKeyframe(idle);
	}
	for (int i = 1; i <= 8; i++) {
		graphics::AnimatedKeyframe running_down = { "runningDown" + std::to_string(i) };
		walk_down.addKeyframe(running_down);
		
		graphics::AnimatedKeyframe running_left = { "runningLeft" + std::to_string(i) };
		walk_left.addKeyframe(running_left);
		
		graphics::AnimatedKeyframe running_right = { "runningRight" + std::to_string(i) };
		walk_right.addKeyframe(running_right);
		
		graphics::AnimatedKeyframe running_up = { "runningUp" + std::to_string(i) };
		walk_up.addKeyframe(running_up);
		
		graphics::AnimatedKeyframe idle = { "idle" + std::to_string(i) };
		idle_animation.addKeyframe(idle);
	}

	walk_up.m_IsLooping = true;
	walk_right.m_IsLooping = true;
	walk_down.m_IsLooping = true;
	walk_left.m_IsLooping = true; 
	idle_animation.m_IsLooping = true;

	walk_up.m_TickBreak = 10;
	walk_right.m_TickBreak = 10;
	walk_down.m_TickBreak = 10;
	walk_left.m_TickBreak = 10;
	idle_animation.m_TickBreak = 20;

	walk_right.play();
	walk_left.play();
	walk_down.play();
	walk_up.play();
	idle_animation.play();
}

std::string PlayerAnimation::update(int player_state, int move_direction, float dt) {

	if (player_state == PlayerStates::IN_TRANSIT) {
		if (move_direction == PlayerMoveDirection::RIGHT) {
			walk_right.update(dt);
			return walk_right.m_CurrentTextureName;
		}
		else if (move_direction == PlayerMoveDirection::LEFT) {
			walk_left.update(dt);
			return walk_left.m_CurrentTextureName;
		}
		else if (move_direction == PlayerMoveDirection::DOWN) {
			walk_down.update(dt);
			return walk_down.m_CurrentTextureName;
		}
		else if (move_direction == PlayerMoveDirection::UP) {
			walk_up.update(dt);
			return walk_up.m_CurrentTextureName;
		}
	}

	idle_animation.update(dt);
	return idle_animation.m_CurrentTextureName;
}