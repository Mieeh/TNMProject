#include"include/spike.h"

void Spike::update(float dt) {
	switch (current_level) {
	case SPIKE_DOWN:
		break;
	case SPIKE_ALMOST_UP:
		break;
	case SPIKE_FULLY_UP:
		break;
	}
}

void Spike::update_spike_level(unsigned short int level) {
	current_level = level;
}