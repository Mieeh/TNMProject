#pragma once

struct DeathPanel {

	// Constructor 
	DeathPanel();

	// Methods
	void increaseOffset(float dt);
	void decreaseOffset(float dt);

	// Members
	float offset = 0;

};