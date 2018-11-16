#pragma once

#include"player.h"
#include"../../engine/include/enemy.h"

enum CombatResult {
	CLASH,
	ENEMY_DIED,
	PLAYER_DIED,
	PLAYER_BLOCK_CLASH
};

struct Combat {
	static CombatResult perform_combat(EnemyBase &enemy) 
	{
		// 0. Get some stuff
		Player* player = Player::get();

		// Check if the player has a shield
		bool hasShield = false;
		if (player->current_item != nullptr)
			if (player->current_item->type == ItemType::SHIELD)
				hasShield = true;

		// 1. Resolve player taking damage
		int newPlayerHP = player->hp - enemy.damage;
		/* Did the player die? */
		if (newPlayerHP <= 0) {
			player->hp = 0;
			return CombatResult::PLAYER_DIED;
		}

		if(!hasShield)
			player->hp = newPlayerHP;
		// Done with 1

		// 2. Resolve enemy taking damage
		int newEnemyHP = enemy.hp - player->attack;
		/* Did the enemy die? */
		if (newEnemyHP <= 0) {
			enemy.hp = 0;
			return CombatResult::ENEMY_DIED;
		}

		enemy.hp = newEnemyHP;
		// Done with 2

		if (hasShield)
			return PLAYER_BLOCK_CLASH;
		// 3. We made it all the way through with neither of them dying, it's a clash! 
		return CombatResult::CLASH;
	}

};