#pragma once

#include<window/event.h>
using namespace bear;

#include<vector>
typedef std::vector<std::vector<int>> level_list;

struct ILevel {
	virtual void init() = 0; // Called when a level is started
	virtual void on_event(Event& event) = 0; // Called every event
	virtual void update(float dt) = 0; // Called ones each frame used to update game logic
	virtual void render() = 0; // Do rendering here
	virtual level_list& get_level_list() = 0; // The tile list for the current level
};