#pragma once
#include "GameObject.h"

class Player : public GameObject // inherit from GameObject
{
public:

	Player(int x, int y, int width, int height, std::string textureID) : GameObject(x, y, width, height, textureID) {};

	virtual void draw(float interpolation);

	virtual void update();

	virtual void clean();

private:
	void handleInput();
};

