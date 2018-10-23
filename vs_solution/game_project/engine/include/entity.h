#pragma once

#include<graphics/renderable.h>

// Base class for all entities in the engine 
struct Entity {
	~Entity() {
		//std::cout << "Deleted: " << renderable.m_TextureName << std::endl;
	}

	bear::graphics::Renderable renderable;
};