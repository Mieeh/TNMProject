#include<iostream>

#include"engine\bear_game.h"
#include"engine/space.h"
#include"engine/game_systems.h"

using namespace bear;

struct Game :BearClass
{
	Engine* game; // Engine object
	Space space;
	Entity* bitch;

	Game() : space()
	{		
		game = new Engine(this); // Create engine instance
	}

	// ============================== // 

	void init() override {
		// Testing the space 
		bitch = space.addEntity("test");
		bitch->renderable.m_Transform.m_Size = bear::core::Vector2f(100, 100);
		bitch->renderable.m_Color = core::Color::Red();
	}

	void update(float dt) override {

	}

	void render() override {
		Graphics::Instance()->draw(*bitch);
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