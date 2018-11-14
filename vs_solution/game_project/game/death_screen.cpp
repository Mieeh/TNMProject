#include"include/death_screen.h"
#include"../engine/include/engine.h"
#include"include\constants.h"

#include<core\vector2.h>

#define DEFAULT_OFFSET_SPEED 0.0015f

DeathPanel::DeathPanel() {
	// Pass
}

void DeathPanel::increaseOffset(float dt)
{
	if (offset < 1) {
		offset += DEFAULT_OFFSET_SPEED * dt;
	}
	else {
		offset = 1;
	}
}

void DeathPanel::decreaseOffset(float dt)
{
	if (offset > 0) {
		offset -= DEFAULT_OFFSET_SPEED * dt;
	}
	else {
		offset = 0;
	}
}

