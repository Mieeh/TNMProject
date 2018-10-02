#include"space.h"

#include<iostream>

Space::Space()
{

}

Entity * Space::getEntity(const std::string& name)
{
	return entity_list[entity_index_map[name]];
}

Entity* Space::addEntity(const std::string & name)
{
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (entity_list[i] == nullptr) {
			// Found an empty slot inside the array
			int index = i;
			entity_index_map.insert(std::pair<std::string, uint2>(name, i));
			entity_list[i] = new Entity();
			return entity_list[i];
		}
	}

	std::cout << "ERROR: Couldn't add entity! Max size of entities has been reached!" << std::endl;
	return nullptr;
}

Space::~Space()
{
	// Delete all entities in the space
	for (auto const& x : entity_index_map) {
		delete entity_list[x.second];
	}
}
