#pragma once
#include <SDL.h>
#include <vector>
class Vector2D;

class InputHandler
{
private:
	InputHandler() {};
	~InputHandler() {};

	static InputHandler* instance;

	std::vector<SDL_Joystick*> controllers;
	bool isInitialised;

	std::vector<std::pair<Vector2D*, Vector2D*>> controllerValues;

	int joystickDeadZone = 10000;

public:
	static InputHandler* getInstance()
	{
		if (instance == 0)
		{
			instance = new InputHandler();
		}

		return instance;
	}

	void update();
	void clean();

	void initialiseControllers();
	bool controllersInitialised() { return isInitialised; }

	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);
};

