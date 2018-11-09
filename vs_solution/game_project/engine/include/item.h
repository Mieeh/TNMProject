#pragma once

#include<string>

#include"entity.h"

enum ItemType {
	WEAPON,
	HEALTH,
	SHIELD,
	KEY
};

enum ItemState {
	ON_MAP,
	PICKED_UP,
	DISCARDED
};

struct Item {
	ItemType type;
	float value;

	ItemState state;
	Entity entity;
	std::string name;
};