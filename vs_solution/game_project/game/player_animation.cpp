#include"include/player_animation.h"

#include"include/player.h"

PlayerAnimation::PlayerAnimation() {

	for (int i = 1; i <= 2; i++) {
		graphics::AnimatedKeyframe idle_holding_frame = { "idle_holding" + std::to_string(i) };
		idle_holding.addKeyframe(idle_holding_frame);
		graphics::AnimatedKeyframe falling_frame = { "falling" + std::to_string(i) };
		falling_animation.addKeyframe(falling_frame);
	}
	for (int i = 1; i <= 8; i++) {
		graphics::AnimatedKeyframe idle = { "idle1" };
		idle_animation.addKeyframe(idle);
	}
	for (int i = 1; i <= 8; i++) {
		graphics::AnimatedKeyframe running_down = { "runningDown" + std::to_string(i) };
		walk_down.addKeyframe(running_down);
		
		graphics::AnimatedKeyframe running_left = { "runningLeft" + std::to_string(i) };
		walk_left.addKeyframe(running_left);
		
		graphics::AnimatedKeyframe running_right = { "runningRight" + std::to_string(i) };
		walk_right.addKeyframe(running_right);
		
		graphics::AnimatedKeyframe running_up = { "runningUp" + std::to_string(i) };
		walk_up.addKeyframe(running_up);
		
		graphics::AnimatedKeyframe idle = { "idle" + std::to_string(i) };
		idle_animation.addKeyframe(idle);

		// Dead
		graphics::AnimatedKeyframe dead = { "death" + std::to_string(i) };
		death_animation.addKeyframe(dead);

		// Holding animations

		graphics::AnimatedKeyframe running_down_holding = { "runningDown_holding" + std::to_string(i) };
		walk_down_holding.addKeyframe(running_down_holding);

		graphics::AnimatedKeyframe running_left_holding = { "runningLeft_holding" + std::to_string(i) };
		walk_left_holding.addKeyframe(running_left_holding);

		graphics::AnimatedKeyframe running_right_holding = { "runningRight_holding" + std::to_string(i) };
		walk_right_holding.addKeyframe(running_right_holding);

		graphics::AnimatedKeyframe running_up_holding = { "runningUp_holding" + std::to_string(i) };
		walk_up_holding.addKeyframe(running_up_holding);
	}
	// Load attack animations
	for (int i = 1; i <= 16; i++) {
		// Normal no item no sword attack
		graphics::AnimatedKeyframe normal_up = { "attackUp" + std::to_string(i) };
		attack_up.addKeyframe(normal_up);

		graphics::AnimatedKeyframe normal_down = { "attackDown" + std::to_string(i) };
		attack_down.addKeyframe(normal_down);	

		graphics::AnimatedKeyframe normal_left = { "attackLeft" + std::to_string(i) };
		attack_left.addKeyframe(normal_left);

		graphics::AnimatedKeyframe normal_right = { "attackRight" + std::to_string(i) };
		attack_right.addKeyframe(normal_right);

		// Attack with item (not weapon)
		graphics::AnimatedKeyframe item_up = { "attackUp_holding" + std::to_string(i) };
		attack_up_item.addKeyframe(item_up);

		graphics::AnimatedKeyframe item_down = { "attackDown_holding" + std::to_string(i) };
		attack_down_item.addKeyframe(item_down);

		graphics::AnimatedKeyframe item_left = { "attackLeft_holding" + std::to_string(i) };
		attack_left_item.addKeyframe(item_left);

		graphics::AnimatedKeyframe item_right = { "attackRight_holding" + std::to_string(i) };
		attack_right_item.addKeyframe(item_right);

		// Attack with weapon (sword)
		graphics::AnimatedKeyframe sword_up = { "attackUp_sword" + std::to_string(i) };
		attack_up_sword.addKeyframe(sword_up);

		graphics::AnimatedKeyframe sword_down = { "attackDown_sword" + std::to_string(i) };
		attack_down_sword.addKeyframe(sword_down);

		graphics::AnimatedKeyframe sword_left = { "attackLeft_sword" + std::to_string(i) };
		attack_left_sword.addKeyframe(sword_left);

		graphics::AnimatedKeyframe sword_right = { "attackRight_sword" + std::to_string(i) };
		attack_right_sword.addKeyframe(sword_right);
	}

	walk_up.m_IsLooping = true;
	walk_right.m_IsLooping = true;
	walk_down.m_IsLooping = true;
	walk_left.m_IsLooping = true; 
	// Idle
	idle_animation.m_IsLooping = true;
	idle_holding.m_IsLooping = true;
	// Holding
	walk_up_holding.m_IsLooping = true;
	walk_right_holding.m_IsLooping = true;
	walk_down_holding.m_IsLooping = true;
	walk_left_holding.m_IsLooping = true;
	// Falling
	falling_animation.m_IsLooping = true;

	walk_up.m_TickBreak = 10;
	walk_right.m_TickBreak = 10;
	walk_down.m_TickBreak = 10;
	walk_left.m_TickBreak = 10;
	// Holding
	walk_up_holding.m_TickBreak = 10;
	walk_right_holding.m_TickBreak = 10;
	walk_down_holding.m_TickBreak = 10;
	walk_left_holding.m_TickBreak = 10;
	// Death
	death_animation.m_TickBreak = 20;
	// Falling
	falling_animation.m_TickBreak = 15;
	// Idle
	idle_animation.m_TickBreak = 20;
	idle_holding.m_TickBreak = 60;
	// Attack
	attack_down.m_TickBreak = attack_speed;
	attack_up.m_TickBreak = attack_speed;
	attack_left.m_TickBreak = attack_speed;
	attack_right.m_TickBreak = attack_speed;
	attack_down_item.m_TickBreak = attack_item_speed;
	attack_up_item.m_TickBreak = attack_item_speed;
	attack_left_item.m_TickBreak = attack_item_speed;
	attack_right_item.m_TickBreak = attack_item_speed;
	attack_down_sword.m_TickBreak = attack_sword_speed;
	attack_up_sword.m_TickBreak = attack_sword_speed;
	attack_left_sword.m_TickBreak = attack_sword_speed;
	attack_right_sword.m_TickBreak = attack_sword_speed; 

	walk_right.play();
	walk_left.play();
	walk_down.play();
	walk_up.play();
	// Holding
	walk_right_holding.play();
	walk_left_holding.play();
	walk_down_holding.play();
	walk_up_holding.play();

	idle_holding.play();
	idle_animation.play();
	falling_animation.play();
}

std::string PlayerAnimation::update(int player_state, int move_direction, float dt) {

	static Player* player = Player::get();

	if (player->player_state == PlayerStates::OUTRO || player->player_state == PlayerStates::INTRO) {
		falling_animation.update(dt);
		return falling_animation.m_CurrentTextureName;
	}

	if (player->player_state == PlayerStates::DEAD) {
		if (death_animation.m_IsPlaying) {
			// This is a hack-fix 
			if (death_animation.m_CurrentTextureName == "death8") {
				death_animation.stop();
				return "death8";
			}
			death_animation.update(dt);
			return death_animation.m_CurrentTextureName;
		}
		else {
			return "death8";
		}
	}

	if (current_attack_animation == nullptr) {
		if (player_state == PlayerStates::IN_TRANSIT) {
			if (player->current_item == nullptr) {
				if (move_direction == PlayerMoveDirection::RIGHT) {
					walk_right.update(dt);
					return walk_right.m_CurrentTextureName;
				}
				else if (move_direction == PlayerMoveDirection::LEFT) {
					walk_left.update(dt);
					return walk_left.m_CurrentTextureName;
				}
				else if (move_direction == PlayerMoveDirection::DOWN) {
					walk_down.update(dt);
					return walk_down.m_CurrentTextureName;
				}
				else if (move_direction == PlayerMoveDirection::UP) {
					walk_up.update(dt);
					return walk_up.m_CurrentTextureName;
				}
			}
			else {
				if (move_direction == PlayerMoveDirection::RIGHT) {
					walk_right_holding.update(dt);
					return walk_right_holding.m_CurrentTextureName;
				}
				else if (move_direction == PlayerMoveDirection::LEFT) {
					walk_left_holding.update(dt);
					return walk_left_holding.m_CurrentTextureName;
				}
				else if (move_direction == PlayerMoveDirection::DOWN) {
					walk_down_holding.update(dt);
					return walk_down_holding.m_CurrentTextureName;
				}
				else if (move_direction == PlayerMoveDirection::UP) {
					walk_up_holding.update(dt);
					return walk_up_holding.m_CurrentTextureName;
				}
			}
		}

		if (player->current_item == nullptr) {
			idle_animation.update(dt);
			return idle_animation.m_CurrentTextureName;
		}
		else {
			idle_holding.update(dt);
			return idle_holding.m_CurrentTextureName;
		}
	}
	else {
		// We have some attack animation
		if (current_attack_animation->m_IsPlaying) {
			current_attack_animation->update(dt);
			return current_attack_animation->m_CurrentTextureName;
		}
		else {
			// Reset player size & offset
			player->entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE) * PLAYER_SIZE;
			player->set_player_position(player->tile_position);
			player->show_item = true;

			current_attack_animation = nullptr;
			return this->update(player_state, move_direction, dt);
		}
	}
}

void PlayerAnimation::play_attack(int direction)
{
	static Player* player = Player::get();
	PlayerMoveDirection move_direction = static_cast<PlayerMoveDirection>(direction);

	// Check if there's already an attack animation in progress
	if (current_attack_animation != nullptr) {
		current_attack_animation->reset();
		current_attack_animation->stop();
	}

	if (player->current_item == nullptr) {
		switch (move_direction) {
		case PlayerMoveDirection::DOWN:
			current_attack_animation = &attack_down;
			break;
		case PlayerMoveDirection::UP:
			current_attack_animation = &attack_up;
			break;
		case PlayerMoveDirection::LEFT:
			current_attack_animation = &attack_left;
			break;
		case PlayerMoveDirection::RIGHT:
			current_attack_animation = &attack_right;
			break;
		}
	}
	else {
		// This is a case where the player either holds a shield/food item or the sword
		if (player->current_item->type == ItemType::WEAPON) {
			switch (move_direction) {
			case PlayerMoveDirection::DOWN:
				current_attack_animation = &attack_down_sword;
				break;
			case PlayerMoveDirection::UP:
				current_attack_animation = &attack_up_sword;
				break;
			case PlayerMoveDirection::LEFT:
				current_attack_animation = &attack_left_sword;
				break;
			case PlayerMoveDirection::RIGHT:
				current_attack_animation = &attack_right_sword;
				break;
			}
			// Resize the player because the animation is 2x the normal sprite size
			player->entity.renderable.m_Transform.m_Size = player->entity.renderable.m_Transform.m_Size * 2;
			player->entity.renderable.m_Transform.m_Position = player->world_position - core::Vector2f(TILE_SIZE, TILE_SIZE) * 0.5f;
			player->show_item = false;
		}
		else {
			switch (move_direction) {
			case PlayerMoveDirection::DOWN:
				current_attack_animation = &attack_down_item;
				break;
			case PlayerMoveDirection::UP:
				current_attack_animation = &attack_up_item;
				break;
			case PlayerMoveDirection::LEFT:
				current_attack_animation = &attack_left_item;
				break;
			case PlayerMoveDirection::RIGHT:
				current_attack_animation = &attack_right_item;
				break;
			}
		}
	}

	current_attack_animation->play();
}

void PlayerAnimation::stop_attack()
{
	static Player* player = Player::get();

	if (current_attack_animation != nullptr) {
		// Reset player size & offset
		if (player->current_item != nullptr) {
			if (player->current_item->type == ItemType::WEAPON) {
				player->entity.renderable.m_Transform.m_Size = core::Vector2f(TILE_SIZE, TILE_SIZE) * PLAYER_SIZE;
				player->show_item = true;
				player->entity.renderable.m_Transform.m_Position += core::Vector2f(TILE_SIZE, TILE_SIZE)*0.5f;
			}
		}

		current_attack_animation->stop();
		current_attack_animation->reset();
		current_attack_animation = nullptr;
	}
}

void PlayerAnimation::play_death()
{
	death_animation.reset();
	death_animation.m_CurrentTextureName = "death1";
	death_animation.play();
}

void PlayerAnimation::stop_death()
{
	death_animation.stop();
}
