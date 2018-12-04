#pragma once

#include"../constants.h"

#include<vector>
#include<map>

#include"../../../engine/include/entity.h"
#include"../../../engine/include/level.h"

// Include enemies and such
#include"../enemies/skeleton.h"

using namespace bear;

#define SPIKE_OFFSET core::Vector2f(0, -TILE_SIZE)
#define GATE_OFFSET core::Vector2f(0, -TILE_SIZE);

// Used for simplifly the task of converting a list of integers to a list of entities that can be rendered 
static void levelUtility_ConvertToLevelContent(LevelContent& level_content) {
	
	bool ground_toggle = false;

	level_content.enemies.clear();
	level_content.items.clear();
	level_content.walls_floors.clear();
	level_content.presure_plates.clear();
	level_content.spike_system.spike_entity_list.clear();
	level_content.gates.clear();

	level_list _level_list = level_content.tile_map;
	for (int y = 0; y < _level_list.size(); y++) 
	{ 
		for (int x = 0; x < _level_list.at(y).size(); ++x) 
		{
			core::Vector2f realPosition = core::Vector2f(x*TILE_SIZE, y*TILE_SIZE);
			
			ground_toggle = !ground_toggle;

			int tile_value = _level_list.at(y).at(x);
			if (is_floor_or_wall(tile_value)) {
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
				entity.renderable.m_Layer = LAYER1;

				// Set texture name based on tile value
				{
					// Big switch setting the correct texture for the tile
					std::string temp;
					switch (tile_value) {
					case FLOOR1:
						entity.renderable.m_TextureName = "floor" + std::to_string(ground_toggle);
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
					case GOAL:

						break;
					}
				}
			}
			else if (is_enemy(tile_value)) {

				// Place ground tile under the enemy
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				// Toggle between the two floor types
				entity.renderable.m_TextureName = "floor" + std::to_string(ground_toggle);
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				// Place the enemy with key "key" at correct position with correct enemy object
				core::Vector2i tile_position(x, y);
				std::string key = (std::string)tile_position;
				switch (tile_value) {
				case SKE:
					level_content.enemies.insert(std::pair<std::string, EnemyBase>(key, Skeleton())); // Add enemy to the list
					level_content.enemies.at(key).entity.renderable.m_Transform.m_Position = core::Vector2f((tile_position.x*TILE_SIZE) + SKELETON_OFFSET_X, (tile_position.y*TILE_SIZE) + SKELETON_OFFSET_Y);
					level_content.enemies.at(key).entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE*SKELETON_SIZE_X, TILE_SIZE*SKELETON_SIZE_Y);
					break;
				}

				// Set correct layer according to y
				level_content.enemies.at(key).entity.renderable.m_Layer = LAYER3 + y;
			}
			else if (is_item(tile_value)) {
				// Place ground tile under the item
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				// Toggle between the two floor types
				entity.renderable.m_TextureName = "floor" + std::to_string(ground_toggle);
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				// Item entity position & size
				Item item;
				item.entity.renderable.m_Transform.m_Position = realPosition;
				item.entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE,TILE_SIZE);
				item.state = ItemState::ON_MAP;

				// Place the item with correct key at correct position
				core::Vector2i tile_position(x, y);
				std::string key = (std::string)tile_position;
				switch (tile_value) {
				case WI:
					// Weapon item! set correct sprite & shit
					// Item name, type & value
					item.entity.renderable.m_TextureName = "sword";
					item.type = ItemType::WEAPON;
					item.name = "Weapon";
					item.value = 2; 
					break;
				case HI:
					// Healing item! set correct sprite & shit
					// Item name, type & value
					item.entity.renderable.m_TextureName = "food";
					item.type = ItemType::HEALTH;
					item.name = "Health";
					item.value = 1; 
					break;
				case SI:
					item.entity.renderable.m_TextureName = "shield";
					item.type = ItemType::SHIELD;
					item.name = "Armor";
					item.value = 1;
					break;
				case KI:
					item.entity.renderable.m_TextureName = "key";
					item.type = ItemType::KEY;
					item.name = "Key";
					item.value = 1;
					break;
				}

				item.entity.renderable.m_Layer = LAYER3 + y;
				// Insert into the level content!
				level_content.items.insert(std::pair<std::string, Item>(key, item));
			}
			else if (is_pp(tile_value)) {
				// Place ground tile under the item
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				// Toggle between the two floor types
				entity.renderable.m_TextureName = "floor" + std::to_string(ground_toggle);
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				// Add the presure plate
				PresurePlate pp;
				pp.entity.renderable.m_TextureName = "pp0";
				pp.entity.renderable.m_Transform.m_Position = realPosition;
				pp.entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);
				pp.entity.renderable.m_Layer = LAYER3 + y;

				// Insert presure plate into the pp map
				core::Vector2i tile_position(x, y);
				std::string key = (std::string)tile_position;
				level_content.presure_plates.insert(std::pair<std::string, PresurePlate>(key, pp));
			}
			else if (tile_value == SPIKE) {
				// Place the spike + ground
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				// Toggle between the two floor types
				entity.renderable.m_TextureName = "floor" + std::to_string(ground_toggle);
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				// Spike
				level_content.spike_system.spike_entity_list.push_back(Entity());
				Entity &spike_entity = level_content.spike_system.spike_entity_list.back();
				spike_entity.renderable.m_TextureName = "spike0";
				spike_entity.renderable.m_Transform.m_Position = realPosition + SPIKE_OFFSET;
				spike_entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE * 2);
				spike_entity.renderable.m_Layer = LAYER3 + y;
			}
			else if (is_gate(tile_value)) {
				// Place the spike + ground
				level_content.walls_floors.push_back(Entity());
				Entity& entity = level_content.walls_floors.back();
				// Toggle between the two floor types
				entity.renderable.m_TextureName = "floor" + std::to_string(ground_toggle);
				entity.renderable.m_Transform.m_Position = realPosition;
				entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE);

				GATE_FACE_DIRECTION facing_direction;
				switch (tile_value) {
				case GATE_FACING_RIGHT:
					facing_direction = GATE_FACE_DIRECTION::FACING_RIGHT;
					break;
				case GATE_FACING_LEFT:
					facing_direction = GATE_FACE_DIRECTION::FACING_LEFT;
					break;
				case GATE_FACING_DOWN:
					facing_direction = GATE_FACE_DIRECTION::FACING_DOWN;
					break;
				}

				Gate& gate_entity = Gate(facing_direction);
				gate_entity.entity.renderable.m_Transform.m_Position = realPosition + GATE_OFFSET;
				gate_entity.entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE * 2);
				gate_entity.entity.renderable.m_Layer = LAYER3 + y; 

				// Insert into gate map
				core::Vector2i tile_position(x, y);
				std::string key = (std::string)tile_position;
				level_content.gates.insert(std::pair<std::string, Gate>(key, gate_entity));
			}
		}
	}
}