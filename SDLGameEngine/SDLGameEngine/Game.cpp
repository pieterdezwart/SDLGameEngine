#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";

		int flags = SDL_WINDOW_SHOWN;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		// init the window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window != nullptr) // window init succes
		{
			std::cout << "Window creation success\n";

			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer != nullptr) // renderer init success
			{
				std::cout << "Renderer creation success\n";

				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // r g b alpha
			}
			else
			{
				std::cout << "Renderer init failed\n";
				return false; // render init fail
			}
		}
		else
		{
			std::cout << "Window init failed\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failed\n";
		return false; // SDL init fail
	}

	std::cout << "SDL init success\n";
	running = true; // enable game loop


	// loading animated sprite
	if (!TextureManager::getInstance()->load("Assets/animate2.png", "animate", renderer))
	{
		return false;
	}

	return true;
}

void Game::render()
{
	SDL_RenderClear(renderer); // clear the renderer to the draw color

	TextureManager::getInstance()->draw("animate", 0, 0, 128, 82, renderer);

	TextureManager::getInstance()->drawFrame("animate", 100, 100, 128, 82, 1, currentFrame, renderer);

	SDL_RenderPresent(renderer); // draw to the screen
}

void Game::update()
{
	currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Game::handleEvents()
{
	SDL_Event event;

	// event handling switch case
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
		}
	}
}

void Game::clean()
{
	std::cout << "Cleaning game objects\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
