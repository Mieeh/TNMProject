#pragma once

#include<string>

#include"entity.h"

enum ItemType {
	WEAPON,
	HEALTH,
	KEY
};

enum ItemState {
	ON_MAP,
	PICKED_UP,
	DISCARDED
};

struct Item {
	ItemState state;
	ItemType type;

	Entity entity;
	std::string name;
	float value;
};
