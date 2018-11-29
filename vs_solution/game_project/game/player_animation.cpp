#include"include/player_animation.h"

#include"include/player.h"

PlayerAnimation::PlayerAnimation() {

	for (int i = 1; i <= 2; i++) {
		graphics::AnimatedKeyframe idle_holding_frame = { "idle_holding" + std::to_string(i) };
		idle_holding.addKeyframe(idle_holding_frame);
	}
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

		// Holding animations

		graphics::AnimatedKeyframe running_down_holding = { "runningDown_holding" + std::to_string(i) };
		walk_down_holding.addKeyframe(running_down_holding);

		graphics::AnimatedKeyframe running_left_holding = { "runningLeft_holding" + std::to_string(i) };
		walk_left_holding.addKeyframe(running_left_holding);

		graphics::AnimatedKeyframe running_right_holding = { "runningRight_holding" + std::to_string(i) };
		walk_right_holding.addKeyframe(running_right_holding);

		graphics::AnimatedKeyframe running_up_holding = { "runningUp_holding" + std::to_string(i) };
		walk_up_holding.addKeyframe(running_up_holding);
	}

	walk_up.m_IsLooping = true;
	walk_right.m_IsLooping = true;
	walk_down.m_IsLooping = true;
	walk_left.m_IsLooping = true; 
	// Idle
	idle_animation.m_IsLooping = true;
	idle_holding.m_IsLooping = true;
	// Holding
	walk_up_holding.m_IsLooping = true;
	walk_right_holding.m_IsLooping = true;
	walk_down_holding.m_IsLooping = true;
	walk_left_holding.m_IsLooping = true;

	walk_up.m_TickBreak = 10;
	walk_right.m_TickBreak = 10;
	walk_down.m_TickBreak = 10;
	walk_left.m_TickBreak = 10;
	// Holding
	walk_up_holding.m_TickBreak = 10;
	walk_right_holding.m_TickBreak = 10;
	walk_down_holding.m_TickBreak = 10;
	walk_left_holding.m_TickBreak = 10;

	// Idle
	idle_animation.m_TickBreak = 20;
	idle_holding.m_TickBreak = 60;

	walk_right.play();
	walk_left.play();
	walk_down.play();
	walk_up.play();
	// Holding
	walk_right_holding.play();
	walk_left_holding.play();
	walk_down_holding.play();
	walk_up_holding.play();

	idle_holding.play();
	idle_animation.play();
}

std::string PlayerAnimation::update(int player_state, int move_direction, float dt) {

	static Player* player = Player::get();

	if (player_state == PlayerStates::IN_TRANSIT) {
		if (player->current_item == nullptr) {
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
		else {
			if (move_direction == PlayerMoveDirection::RIGHT) {
				walk_right_holding.update(dt);
				return walk_right_holding.m_CurrentTextureName;
			}
			else if (move_direction == PlayerMoveDirection::LEFT) {
				walk_left_holding.update(dt);
				return walk_left_holding.m_CurrentTextureName;
			}
			else if (move_direction == PlayerMoveDirection::DOWN) {
				walk_down_holding.update(dt);
				return walk_down_holding.m_CurrentTextureName;
			}
			else if (move_direction == PlayerMoveDirection::UP) {
				walk_up_holding.update(dt);
				return walk_up_holding.m_CurrentTextureName;
			}
		}
	}

	if (player->current_item == nullptr) {
		idle_animation.update(dt);
		return idle_animation.m_CurrentTextureName;
	}
	else {
		idle_holding.update(dt);
		return idle_holding.m_CurrentTextureName;
	}
}