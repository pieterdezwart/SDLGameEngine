#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"

class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool running;

	int currentFrame;
	TextureManager textureManager;

public:
	Game();
	~Game();

	// simply set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void render();
	void update();
	void handleEvents();
	void clean();

	// a function to acces the private running variable
	bool getRunning() { return running; }
};

