#include"include/gate.h"

using namespace bear;
using namespace bear::graphics;

#include"include/bear_game.h"

Gate::Gate(GATE_FACE_DIRECTION _facing_direction) : facing_direction(_facing_direction) 
{
	gate_state = GATE_STATE::LOCKED; // Locked by deafult dadoy
	engine = Engine::Instance();

	// Facing direction sprite?
	switch (facing_direction) {
	case GATE_FACE_DIRECTION::FACING_DOWN:
		entity.renderable.m_TextureName = "gateforward1";
		last_frame_name = "gateforward8";
		for (int i = 1; i <= 8; i++) {
			AnimatedKeyframe keyframe = { "gateforward" + std::to_string(i) };
			unlock_animation.addKeyframe(keyframe);
		}
		break;
	case GATE_FACE_DIRECTION::FACING_RIGHT:
		entity.renderable.m_TextureName = "gateFacingRight1";
		last_frame_name = "gateFacingRight8";
		for (int i = 0; i <= 8; i++) {
			AnimatedKeyframe keyframe = { "gateFacingRight" + std::to_string(i) };
			unlock_animation.addKeyframe(keyframe);
		}
		break;
	case GATE_FACE_DIRECTION::FACING_LEFT:
		entity.renderable.m_TextureName = "gateFacingLeft1";
		last_frame_name = "gateFacingLeft8";
		for (int i = 1; i <= 8; i++) {
			AnimatedKeyframe keyframe = { "gateFacingLeft" + std::to_string(i) };
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
