#include "InputHandler.h"
#include <iostream>
#include "Game.h"
#include "Vector2D.h"

InputHandler* InputHandler::instance = 0;

void InputHandler::initialiseControllers()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if (joy)
			{
				controllers.push_back(joy);
				controllerValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0))); // add our pair
			}
			else
			{
				std::cout << SDL_GetError();
			}
		}

		SDL_JoystickEventState(SDL_ENABLE);
		isInitialised = true;

		std::cout << "Initialised " << controllers.size() << " controllers";
	}
	else
	{
		isInitialised = false;
	}
}

void InputHandler::update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			Game::getInstance()->clean();
		}

		if (event.type == SDL_JOYAXISMOTION)
		{
			int whichOne = event.jaxis.which;

			// left stick move left or right
			if (event.jaxis.axis == 0)
			{
				if (event.jaxis.value > joystickDeadZone)
				{
					controllerValues[whichOne].first->setX(1);
				}
				else if (event.jaxis.value < -joystickDeadZone)
				{
					controllerValues[whichOne].first->setX(-1);
				}
				else
				{
					controllerValues[whichOne].first->setX(0);
				}
			}

			// left stick move up or down
			if (event.jaxis.axis == 1)
			{
				if (event.jaxis.value > joystickDeadZone)
				{
					controllerValues[whichOne].first->setY(1);
				}
				else if (event.jaxis.value < -joystickDeadZone)
				{
					controllerValues[whichOne].first->setY(-1);
				}
				else
				{
					controllerValues[whichOne].first->setY(0);
				}
			}

			// right stick move left or right
			if (event.jaxis.axis == 3)
			{
				if (event.jaxis.value > joystickDeadZone)
				{
					controllerValues[whichOne].second->setX(1);
				}
				else if (event.jaxis.value < -joystickDeadZone)
				{
					controllerValues[whichOne].second->setX(-1);
				}
				else
				{
					controllerValues[whichOne].second->setX(0);
				}
			}

			// right stick move up or down
			if (event.jaxis.axis == 4)
			{
				if (event.jaxis.value > joystickDeadZone)
				{
					controllerValues[whichOne].second->setY(1);
				}
				else if (event.jaxis.value < -joystickDeadZone)
				{
					controllerValues[whichOne].second->setY(-1);
				}
				else
				{
					controllerValues[whichOne].second->setY(0);
				}
			}
		}
	}
}

int InputHandler::xvalue(int joy, int stick)
{
	if (controllerValues.size() > 0)
	{
		if (stick == 1)
		{
			return controllerValues[joy].first->getX();
		}
		else if (stick == 2)
		{
			return controllerValues[joy].second->getX();
		}
	}
	return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
	if (controllerValues.size() > 0)
	{
		if (stick == 1)
		{
			return controllerValues[joy].first->getY();
		}
		else if (stick == 2)
		{
			return controllerValues[joy].second->getY();
		}
	}
	return 0;
}

void InputHandler::clean()
{
	if (isInitialised)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(controllers[i]);
		}
	}
}