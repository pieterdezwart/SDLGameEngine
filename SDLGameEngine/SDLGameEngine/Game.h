#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Game
{
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

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* texture; // the new SDL_Texture variable
	SDL_Rect sourceRectangle; // the first rectangle
	SDL_Rect destinationRectangle; // another rectangle

	bool running;
};

