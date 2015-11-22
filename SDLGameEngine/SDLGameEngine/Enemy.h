#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(int x, int y, int width, int height, std::string textureID) : GameObject(x, y, width, height, textureID) {};

	virtual void draw(float interpolation);
	virtual void update();
	virtual void clean();
};

