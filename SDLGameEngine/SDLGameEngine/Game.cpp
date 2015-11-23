#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

Game* Game::instance = 0;

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

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // r g b alpha
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

	InputHandler::getInstance()->initialiseControllers();

	gameStateMachine = new GameStateMachine();

	gameStateMachine->changeState(new MenuState());

	// loading textures
	if (!TextureManager::getInstance()->load("Assets/animate2.png", "animate", renderer))
	{
		return false;
	}


	// loading objects
	gameObjects.push_back(new Player(100, 100, 128, 82, "animate"));
	gameObjects.push_back(new Enemy(300, 300, 128, 82, "animate"));


	return true;
}

void Game::render(float interpolation)
{
	SDL_RenderClear(renderer); // clear the renderer to the draw color

	//for (GameObject* obj : gameObjects)
	//{
	//	obj->draw(interpolation);
	//}

	gameStateMachine->render(interpolation);

	SDL_RenderPresent(renderer); // draw to the screen
}

void Game::update()
{
	//for (GameObject* obj : gameObjects)
	//{
	//	obj->update();
	//}

	gameStateMachine->update();
}

void Game::handleEvents()
{
	InputHandler::getInstance()->update();

	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		gameStateMachine->changeState(new PlayState());
	}
}

void Game::clean()
{
	InputHandler::getInstance()->clean();

	std::cout << "Cleaning game objects\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
