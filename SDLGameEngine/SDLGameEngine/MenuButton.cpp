#include "MenuButton.h"
#include "InputHandler.h"
#include "Game.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include "MenuState.h"


void MenuButton::draw(float interpolation)
{
	GameObject::draw(interpolation);
}

void MenuButton::update()
{
	Vector2D mousePos = InputHandler::getInstance()->getMousePosition();

	if (mousePos.getX() < (position.getX() + width)
		&& mousePos.getX() > position.getX()
		&& mousePos.getY() < (position.getY() + height)
		&& mousePos.getY() > position.getY())
	{
		currentFrame = MOUSE_OVER;
		if (InputHandler::getInstance()->getMouseButtonState(LEFT))
		{
			currentFrame = CLICKED;

			if (getTextureID() == "exitbutton")
			{
				Game::getInstance()->clean();
			}

			if (getTextureID() == "playbutton")
			{
				Game::getInstance()->getStateMachine()->changeState(new PlayState());
			}

			if (getTextureID() == "resumebutton")
			{
				Game::getInstance()->getStateMachine()->popState();
			}

			if (getTextureID() == "mainbutton")
			{
				Game::getInstance()->getStateMachine()->changeState(new MenuState());
			}

			if (getTextureID() == "restartbutton")
			{
				Game::getInstance()->getStateMachine()->changeState(new PlayState());
			}

			buttonReleased = false;
		}
		else if (!InputHandler::getInstance()->getMouseButtonState(LEFT))
		{
			buttonReleased = true;
			currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	GameObject::clean();
}