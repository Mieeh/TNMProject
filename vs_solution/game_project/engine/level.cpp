#include"include/level.h"

void LevelContent::update(float dt)
{
	for (auto &x : gates) {
		x.second.update(dt);
	}
	spike_system.update(dt);
}