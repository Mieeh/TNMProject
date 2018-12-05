#include"include/spike_system.h"

#include"include/bear_game.h"

using namespace bear;
using namespace bear::graphics;

SpikeSystem::SpikeSystem()
{
	engine = Engine::Instance();

	// Setup the animated renderables
	for (int i = 1; i <= 4; i++) {
		AnimatedKeyframe keyframe = { "spike" + std::to_string(i) };
		spike_go_up.addKeyframe(keyframe);
	}
	for (int i = 4; i >= 0; i--) {
		AnimatedKeyframe keyframe = { "spike" + std::to_string(i) };
		spike_go_down.addKeyframe(keyframe);
	}

	spike_go_down.m_TickBreak = 15;
	spike_go_down.m_IsLooping = false;
	spike_go_up.m_TickBreak = 15;
	spike_go_up.m_IsLooping = false;

	texture_name = "spike0";

	spike_go_down.play();
}

void SpikeSystem::reset_spikes()
{
	current_spike_level = 0;
}

void SpikeSystem::incement_spike_level()
{
	if (current_spike_level == 3) {
		current_spike_level = 0;
	}
	else {
		current_spike_level++;

		if (current_spike_level == 3) {
			spike_go_up.reset();
			spike_go_up.m_CurrentTextureName = "spike1";
			spike_go_up.play();
		}
	}
}

void SpikeSystem::update(float dt)
{	
	switch (current_spike_level) {
	case 0:
	case 1:
		if (texture_name != "spike0") {
			spike_go_down.update(dt);
			texture_name = spike_go_down.m_CurrentTextureName;
		}
		else {
			texture_name = "spike0";
			spike_go_down.reset();
			spike_go_down.m_CurrentTextureName = "spike4";
		}
		break;
	case 2:
		texture_name = "spike1";
		break;

	case 3:
		if (spike_go_up.m_CurrentTextureName == "spike4") {
			spike_go_up.stop();
			texture_name = "spike4";
		}
		else {
			spike_go_up.update(dt);
			texture_name = spike_go_up.m_CurrentTextureName;
		}
		break;
	}
	for (Entity& entity : spike_entity_list) {
		entity.renderable.m_TextureName = texture_name;
	}
}

void SpikeSystem::render()
{
	for (Entity& entity : spike_entity_list) {
		engine->graphics_manager->draw(entity);
	}
}