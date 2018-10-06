#include"game\game.h"

#include<filesystem>
namespace fs = std::experimental::filesystem;

int main()
{
	Game *game = new Game();
	delete game;

	return 0;
}