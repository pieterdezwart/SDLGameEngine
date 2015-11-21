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

	/* 
	// Loading single image
	SDL_Surface* tempSurface = SDL_LoadBMP("Assets/duckhunt.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_FreeSurface(tempSurface);

	SDL_QueryTexture(texture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);

	sourceRectangle.w = 50;
	sourceRectangle.h = 50;

	sourceRectangle.x = 50;
	sourceRectangle.y = 50;

	destinationRectangle.x = 100;
	destinationRectangle.y = 100;

	//destinationRectangle.x = sourceRectangle.x = 0;
	//destinationRectangle.y = sourceRectangle.y = 0;
	destinationRectangle.w = sourceRectangle.w;
	destinationRectangle.h = sourceRectangle.h;
	*/

	// loading animated sprite
	SDL_Surface* tempSurface = IMG_Load("Assets/animate2.png");
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_FreeSurface(tempSurface);

	SDL_QueryTexture(texture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);

	destinationRectangle.x = sourceRectangle.x = 0;
	destinationRectangle.y = sourceRectangle.y = 0;

	sourceRectangle.w = 128;
	sourceRectangle.h = 82;

	destinationRectangle.w = sourceRectangle.w;
	destinationRectangle.h = sourceRectangle.h;

	return true;
}

void Game::render()
{
	SDL_RenderClear(renderer); // clear the renderer to the draw color

	SDL_RenderCopyEx(renderer, texture, &sourceRectangle, &destinationRectangle, 0, 0, SDL_FLIP_NONE); // single image

	SDL_RenderPresent(renderer); // draw to the screen
}

void Game::update()
{
	sourceRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6));
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
