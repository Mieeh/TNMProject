#pragma once

#include"player.h"
#include"../../engine/include/enemy.h"

enum CombatResult {
	CLASH,
	ENEMY_DIED,
	PLAYER_DIED,
};

struct Combat {
	static CombatResult perform_combat(EnemyBase &enemy) 
	{
		// 0. Get some stuff
		Player* player = Player::get();

		// Check if the player has a shield or a weapon
		bool hasItem = false;
		ItemType itemType;
		if (player->current_item != nullptr) {
			if (player->current_item->type == ItemType::SHIELD || player->current_item->type == ItemType::WEAPON) {
				itemType = player->current_item->type;
				hasItem = true;
			}
			// Shield is one time use then discarded
			if (itemType == ItemType::SHIELD) {
				player->current_item = nullptr;
				// Play the armor destroyed sfx
				Engine::Instance()->sound_manager->get_sfx("armor_break")->sf_sound.play();
			}
		}

		// 1. Resolve player taking damage
		int newPlayerHP = player->hp - enemy.damage;	
		if (hasItem && itemType == ItemType::SHIELD)
			newPlayerHP = player->hp;

		/* Did the player die? */
		if (newPlayerHP <= 0) {
			player->hp = 0;
			return CombatResult::PLAYER_DIED;
		}

		player->hp = newPlayerHP;

		// 2. Resolve enemy taking damage
		int newEnemyHP = enemy.hp - (player->attack);
		if (hasItem && itemType == ItemType::WEAPON) {
			newEnemyHP = 0;
		}

		/* Did the enemy die? */
		if (newEnemyHP <= 0) {
			enemy.hp = 0;
			return CombatResult::ENEMY_DIED;
		}

		enemy.hp = newEnemyHP;

		// 3. We made it all the way through with neither of them dying, it's a clash! 
		return CombatResult::CLASH;
	}

};