#pragma once

#include<map>
#include<string>

#define MAX_ENTITIES 100

#include"typedefs.h"
#include"entity.h"

struct Space {
	// Data
	std::map<std::string, uint2> entity_index_map;
	Entity* entity_list[MAX_ENTITIES] = { nullptr };

	// Methods
	Space();
	~Space();
	Entity* getEntity(const std::string& name);
	Entity* addEntity(const std::string& name);
};