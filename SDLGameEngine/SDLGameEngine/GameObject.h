#pragma once
#include <SDL.h>
#include <iostream>
#include "Vector2D.h"


class GameObject
{
public:
	virtual void draw(float interpolation) = 0; // 0 makes it a pure virtual function, derived classes have to implement them
	virtual void update() = 0;
	virtual void clean() = 0;

	int getWidth() { return width; }
	int getHeight() { return height; }
	std::string getTextureID() { return textureID; }

protected:
	GameObject(int x, int y, int width, int height, std::string textureID) : position(x,y), velocity(0, 0)
	{
		
		this->width = width;
		this->height = height;
		this->textureID = textureID;

		currentRow = 1;
		currentFrame = 1;
	}

	virtual ~GameObject() {}

	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;

	int width, height;

	int currentFrame;
	int currentRow;

	std::string textureID;
};

