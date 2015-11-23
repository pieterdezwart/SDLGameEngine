#pragma once
#include <SDL.h>
#include <vector>
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
private:
	InputHandler();
	~InputHandler() {};

	static InputHandler* instance;

	std::vector<SDL_Joystick*> controllers;
	bool isInitialised;

	std::vector<std::pair<Vector2D*, Vector2D*>> controllerValues;

	int joystickDeadZone = 10000;

	std::vector<std::vector<bool>> buttonStates;

	std::vector<bool> mouseButtonStates;

	Vector2D mousePosition;

	const Uint8* keystates;

	// private functions to handle different event types
	
	// handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// handle joysticks events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

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

	bool getButtonState(int joy, int buttonNumber)
	{
		return buttonStates[joy][buttonNumber];
	}

	bool getMouseButtonState(int buttonNumber)
	{
		return mouseButtonStates[buttonNumber];
	}

	Vector2D getMousePosition()
	{
		return mousePosition;
	}

	bool isKeyDown(SDL_Scancode key);

};

