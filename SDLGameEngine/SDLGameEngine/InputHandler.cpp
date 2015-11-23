#include "InputHandler.h"
#include <iostream>
#include "Game.h"
#include "Vector2D.h"

InputHandler* InputHandler::instance = 0;

InputHandler::InputHandler()
{
	for (int i = 0; i < 3; i++)
	{
		mouseButtonStates.push_back(false);
	}
}

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

				std::vector<bool> tempButtons;

				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}

				buttonStates.push_back(tempButtons);
			}
			else
			{
				std::cout << SDL_GetError();
			}
		}

		SDL_JoystickEventState(SDL_ENABLE);
		isInitialised = true;

		std::cout << "Initialised " << controllers.size() << " controllers\n";
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
		switch (event.type)
		{
		case SDL_QUIT:
			Game::getInstance()->clean();
			break;

		case SDL_JOYAXISMOTION:
			onJoystickAxisMove(event);
			break;

		case SDL_JOYBUTTONDOWN:
			onJoystickButtonDown(event);
			break;

		case SDL_JOYBUTTONUP:
			onJoystickButtonUp(event);
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;

		default:
			break;
		}

	}
}

void InputHandler::onKeyDown()
{
	keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event & event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		mousePosition.setX(event.motion.x);
		mousePosition.setY(event.motion.y);
	}
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onJoystickAxisMove(SDL_Event & event)
{
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

void InputHandler::onJoystickButtonDown(SDL_Event & event)
{
	if (event.type == SDL_JOYBUTTONDOWN)
	{
		int whichOne = event.jaxis.which;
		buttonStates[whichOne][event.jbutton.button] = true;
	}

}

void InputHandler::onJoystickButtonUp(SDL_Event & event)
{
	if (event.type == SDL_JOYBUTTONUP)
	{
		int whichOne = event.jaxis.which;
		buttonStates[whichOne][event.jbutton.button] = false;
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

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (keystates != 0)
	{
		if (keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
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