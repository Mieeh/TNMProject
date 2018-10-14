#pragma once

#include"../constants.h"

#include<vector>
#include<map>

#include"../../../engine/include/entity.h"
#include"../../../engine/include/level.h"

// Include enemies and such
#include"../enemies/bat.h"

using namespace bear;

// Used for simplifly the task of converting a list of integers to a list of entities that can be rendered 
static void levelUtility_ConvertToLevelContent(LevelContent& level_content) {
	level_list _level_list = level_content.tile_map;
	for (int y = 0; y < _level_list.size(); y++) 
	{ 
		for (int x = 0; x < _level_list.at(y).size(); ++x) 
		{
			core::Vector2f realPosition = core::Vector2f(x*TILE_SIZE, y*TILE_SIZE);
			
			int tile_value = _level_list.at(y).at(x);
			if (tile_value != -1) {
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				// Set texture name based on tile value
				{
					switch (tile_value) {
					case FLOOR1:
						entity.renderable.m_TextureName = "ground";
						break;
					case WALL_TOP:
						entity.renderable.m_TextureName = "wallTop";
						break;
					case PIT:
						entity.renderable.m_TextureName = "pit";
						break;
					case WALL_LEFT:
						entity.renderable.m_TextureName = "wallLeft";
						break;
					case WALL_RIGHT:
						entity.renderable.m_TextureName = "wallRight";
						break;
					case BOTTOM_LEFT_WALL:
						entity.renderable.m_TextureName = "bottomLeftWall";
						break;
					case BOTTOM_RIGHT_WALL:
						entity.renderable.m_TextureName = "bottomRightWall";
						break;
					}
				}

				if (is_enemy(tile_value)) {
					entity.renderable.m_TextureName = "ground";
					core::Vector2i tile_position(x, y);
					std::string key = (std::string)tile_position;
					switch (tile_value) {
					case BAT:
						level_content.enemies.insert(std::pair<std::string, EnemyBase>(key, Bat())); // Add enemy to the list
						level_content.enemies.at(key).entity.renderable.m_TextureName = "test_enemy";
						level_content.enemies.at(key).entity.renderable.m_Transform.m_Position = core::Vector2f((tile_position.x*TILE_SIZE) + BAT_OFFSET_X, (tile_position.y*TILE_SIZE) + BAT_OFFSET_Y);
						level_content.enemies.at(key).entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE*BAT_SIZE_X, TILE_SIZE*BAT_SIZE_Y);
						break;
					}

					level_content.enemies.at(key).entity.renderable.m_Layer = y;
				}
			}
		}
	}
}