#include"include/player_ui.h"

#include"include/player.h"

#define FOOD_SPRITE_SIZE 64

PlayerUI::PlayerUI()
{
	engine = Engine::Instance();

	for (int i = 0; i < 5; i++) {
		food_entities[i] = Entity();
		food_entities[i].renderable.m_TextureName = "food";
		food_entities[i].renderable.m_Transform.m_Size = core::Vector2f(FOOD_SPRITE_SIZE, FOOD_SPRITE_SIZE);
		food_entities[i].renderable.m_Transform.m_Position = core::Vector2f(i*(FOOD_SPRITE_SIZE / 2), 0);
	}
}

void PlayerUI::render_player_hp()
{
	for (int i = 0; i < 5; i++) {
		if (i < Player::get()->hp) {
			food_entities[i].renderable.m_Color = core::Color::White();
		}
		else {
			food_entities[i].renderable.m_Color.a = 0.2f;
		}
		engine->graphics_manager->draw_as_ui(food_entities[i]);
	}
}