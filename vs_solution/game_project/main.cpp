#include<iostream>

#include"engine\bear_game.h"
#include"engine/space.h"

using namespace bear;

struct Game :BearClass
{
	Engine* game; // Engine object
	Space space;

	Game() : space()
	{		
		game = new Engine(this); // Create engine instance
	}

	// ============================== // 

	void init() override {
		// Testing the space 
		space.addEntity("test");
	}

	void update(float dt) override {

	}

	void on_event(Event& event) override {
		if (event.type == EventType::KeyPressed) {
			std::cout << "Game key was pressed!" << std::endl;
		}
	}

	void exit() override {
		std::cout << "Bye game!!!" << std::endl;
	}
};

int main()
{
	Game *game = new Game();
	delete game;

	return 0;
}