#pragma once

#include"../constants.h"

#include<vector>
#include"../../../engine/include/entity.h"
#include<core\vector2.h>

using namespace bear;

// Used for simplifly the task of converting a list of integers to a list of entities that can be rendered 
static void levelUtility_ConvertToEntities(level_list& _level_list, std::vector<Entity>& entity_list) {
	for (int y = 0; y < _level_list.size(); y++) 
	{ 
		for (int x = 0; x < _level_list.at(y).size(); ++x) 
		{
			core::Vector2f realPosition = core::Vector2f(x*TILE_SIZE, y*TILE_SIZE);
			
			entity_list.push_back(Entity());
			Entity& entity = entity_list.back();
			entity.renderable.m_Transform.m_Position = realPosition;
			entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

			// Set texture name based on tile value
			{
				int tileValue = _level_list.at(y).at(x);
				switch (tileValue) {
				case FLOOR1:
					entity.renderable.m_TextureName = "floor";
					break;
				case WALL_LEFT:
					entity.renderable.m_TextureName = "wallLeft";
					break;
				case WALL_RIGHT:
					entity.renderable.m_TextureName = "wallRight";
					break;
				case WALL_TOP:
					entity.renderable.m_TextureName = "wallTop";
					break;
				case WALL_BOTTOM:
					entity.renderable.m_TextureName = "wallBottom";
					break;
				case WALL_BOTTOM_LEFT_CORNER:
					entity.renderable.m_TextureName = "bottomLeftCorner";
					break;
				case WALL_BOTTOM_RIGHT_CORNER:
					entity.renderable.m_TextureName = "bottomRightCorner";
					break;
				case WALL_TOP_LEFT_CORNER:
					entity.renderable.m_TextureName = "topLeftCorner";
					break;
				case WALL_TOP_RIGHT_CORNER:
					entity.renderable.m_TextureName = "topRightCorner";
					break;
				}
			}
		}
	}
}