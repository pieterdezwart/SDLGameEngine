#pragma once
#include "GameObject.h"

class MenuButton : public GameObject
{
public:
	MenuButton(int x, int y, int width, int height, std::string textureID) : GameObject(x, y, width, height, textureID) 
	{
		currentFrame = MOUSE_OUT; // start at frame 0
	};

	virtual void draw(float interpolation);

	virtual void update();

	virtual void clean();


private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 1
	};

	bool buttonReleased;
};

