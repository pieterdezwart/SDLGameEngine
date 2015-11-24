#include "Game.h"


int main(int argc, char* args[])
{

	std::cout << "Game init attempt...\n";

	if (Game::getInstance()->init("SDL Window", 100, 100, 640, 480, false))
	{
		int FPS = 25;
		int DELAY_TIME = 1000 / FPS;
		int MAX_FRAMESKIP = 5;

		int lastTime = SDL_GetTicks(); // number of milliseconds since start of the game
		int accumulator = 0;
		float interpolation;

		std::cout << "Game init success\n";
		while (Game::getInstance()->getRunning())
		{
			Game::getInstance()->handleEvents();

			accumulator = 0;
			while (SDL_GetTicks() > lastTime && accumulator < MAX_FRAMESKIP)
			{
				Game::getInstance()->update();

				lastTime += DELAY_TIME;
				accumulator++;
			}

			interpolation = float(SDL_GetTicks() + DELAY_TIME - lastTime) / float(DELAY_TIME);

			Game::getInstance()->render(interpolation);

		}

	}
	else
	{
		std::cout << "Game init failure - " << SDL_GetError() << "\n";
		return -1;
	}

	std::cout << "Game closing...\n";
	Game::getInstance()->clean();

	return 0;
}