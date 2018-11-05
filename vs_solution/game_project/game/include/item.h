#pragma once

#include<string>

enum ItemType {
	WEAPON,
	HEALTH,
	KEY
};

struct Item {
	std::string name;
	float value;
};
