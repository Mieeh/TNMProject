#include<iostream>

#include"engine\bear_game.h"

using namespace bear;

struct Game :BearClass
{
	Engine* game; // Engine object

	Game()
	{
		game = new Engine(this);
	}

	// ============================== // 

	void init() override {
		std::cout << "Game was init()" << std::endl;
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

	system("pause>null");
	return 0;
}