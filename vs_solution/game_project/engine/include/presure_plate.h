#pragma once

#include"../../engine/include/entity.h"

struct PresurePlate {
	Entity entity;
	bool is_on = false;

	void toggle()
	{
		is_on = !is_on; // Toggle the bool
		entity.renderable.m_TextureName = "pp" + std::to_string(is_on);
	}
};