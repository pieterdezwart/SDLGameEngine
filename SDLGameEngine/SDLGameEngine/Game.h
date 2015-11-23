#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class GameObject;
class GameStateMachine;

class Game
{
private:
	Game() {};

	// create the instance member variable
	static Game* instance;

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool running;

	std::vector<GameObject*> gameObjects;

	GameStateMachine* gameStateMachine;

public:
	static Game* getInstance()
	{
		if (instance == 0)
		{
			instance = new Game();
			return instance;
		}
		return instance;
	}

	~Game();

	SDL_Renderer* getRenderer() const { return renderer; }

	// simply set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void render(float interpolation);
	void update();
	void handleEvents();
	void clean();

	// a function to acces the private running variable
	bool getRunning() { return running; }
};

