#include"include/gate.h"

using namespace bear;
using namespace bear::graphics;

#include"include/bear_game.h"

Gate::Gate(GATE_FACE_DIRECTION _facing_direction, GATE_TYPE _gate_type) : facing_direction(_facing_direction), gate_type(_gate_type)
{
	gate_state = GATE_STATE::LOCKED; // Locked by deafult dadoy
	engine = Engine::Instance();

	// Wow...
	std::string red_literal = "";
	if (gate_type == GATE_TYPE::RED) {
		red_literal = "_red";
	}

	// Facing direction sprite?
	switch (facing_direction) {
	case GATE_FACE_DIRECTION::FACING_DOWN:
		entity.renderable.m_TextureName = std::string("gateforward") + red_literal + "1";
		last_frame_name = std::string("gateforward") + red_literal + "8";
		for (int i = 1; i <= 8; i++) {
			AnimatedKeyframe keyframe = { "gateforward" + red_literal + std::to_string(i) };
			unlock_animation.addKeyframe(keyframe);
		}
		break;
	case GATE_FACE_DIRECTION::FACING_RIGHT:
		entity.renderable.m_TextureName = std::string("gateFacingRight") + red_literal + "1";
		last_frame_name = std::string("gateFacingRight") + red_literal + "8";
		for (int i = 1; i <= 8; i++) {
			AnimatedKeyframe keyframe = { "gateFacingRight" + red_literal + std::to_string(i) };
			unlock_animation.addKeyframe(keyframe);
		}
		break;
	case GATE_FACE_DIRECTION::FACING_LEFT:
		entity.renderable.m_TextureName = std::string("gateFacingLeft") + red_literal + "1";
		last_frame_name = std::string("gateFacingLeft") + red_literal + "8";
		for (int i = 1; i <= 8; i++) {
			AnimatedKeyframe keyframe = { "gateFacingLeft" + red_literal + std::to_string(i) };
			unlock_animation.addKeyframe(keyframe);
		}
		break;
	case GATE_FACE_DIRECTION::FACING_UP:
		entity.renderable.m_TextureName = std::string("gateupward") + red_literal + "1";
		last_frame_name = std::string("gateupward") + red_literal + "8";
		for (int i = 1; i <= 8; i++) {
			AnimatedKeyframe keyframe = { "gateupward" + red_literal + std::to_string(i) };
			unlock_animation.addKeyframe(keyframe);
		}
		break;
	}

	unlock_animation.m_TickBreak = 15;
}

void Gate::unlock()
{
	gate_state = GATE_STATE::UNLOCKING;
	unlock_animation.play();
}

void Gate::update(float dt)
{
	if (gate_state == GATE_STATE::UNLOCKING) {
		if (unlock_animation.m_CurrentTextureName == last_frame_name) {
			unlock_animation.stop();
			gate_state = GATE_STATE::UNLOCKED;
		}
		unlock_animation.update(dt);
		entity.renderable.m_TextureName = unlock_animation.m_CurrentTextureName;
	}
}
