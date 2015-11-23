#include "MenuButton.h"
#include "InputHandler.h"


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