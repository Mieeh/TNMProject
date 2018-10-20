#include"include/death_screen.h"
#include"../engine/include/engine.h"
#include"include\constants.h"

#include<core\vector2.h>

#define DEFAULT_FADE_SPEED 0.005f

DeathPanel::DeathPanel() : a(0.0f), fade_speed(DEFAULT_FADE_SPEED) {

	entity.renderable.m_TextureName = "death_screen";
	entity.renderable.m_Color.a = a;
	entity.renderable.m_Transform.m_Size = bear::core::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
	entity.renderable.m_Layer = LAYER3;
}

void DeathPanel::fade_to_1(float dt) {
	if (a <= 1) {
		bear::core::lerp(a, 1.1f, fade_speed*dt);
		entity.renderable.m_Color.a = a;
	}
}

void DeathPanel::fade_to_0(float dt) {
	if (a >= 0) {
		bear::core::lerp(a, -0.1f, fade_speed*dt);
		entity.renderable.m_Color.a = a;
	}
}
