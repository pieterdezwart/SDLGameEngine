#include "Game.h"

Game* game = nullptr;

int main(int argc, char* args[])
{
	game = new Game();

	game->init("SDL Window", 100, 100, 640, 480, false);

	while (game->getRunning())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}