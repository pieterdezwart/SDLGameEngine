#include "Player.h"
#include "InputHandler.h"

void Player::draw(float interpolation)
{
	GameObject::draw(interpolation);
}

void Player::update()
{
	velocity.setX(0);
	velocity.setY(0);

	handleInput();

	currentFrame = int(((SDL_GetTicks() / 100) % 6));

	GameObject::update();
}

void Player::clean()
{

}

void Player::handleInput()
{
	if (InputHandler::getInstance()->controllersInitialised())
	{
		if (InputHandler::getInstance()->xvalue(0, 1) > 0 || InputHandler::getInstance()->xvalue(0, 1) < 0)
		{
			velocity.setX(1 * InputHandler::getInstance()->xvalue(0, 1));
		}

		if (InputHandler::getInstance()->yvalue(0, 1) > 0 || InputHandler::getInstance()->yvalue(0, 1) < 0)
		{
			velocity.setY(1 * InputHandler::getInstance()->yvalue(0, 1));
		}

		if (InputHandler::getInstance()->xvalue(0, 2) > 0 || InputHandler::getInstance()->xvalue(0, 2) < 0)
		{
			velocity.setX(1 * InputHandler::getInstance()->xvalue(0, 2));
		}

		if (InputHandler::getInstance()->yvalue(0, 2) > 0 || InputHandler::getInstance()->yvalue(0, 2) < 0)
		{
			velocity.setY(1 * InputHandler::getInstance()->yvalue(0, 2));
		}

		if (InputHandler::getInstance()->getButtonState(0, 3))
		{
			velocity.setX(1);
		}
	}

	if (InputHandler::getInstance()->getMouseButtonState(LEFT))
	{
		//velocity.setX(1);

		Vector2D vec = InputHandler::getInstance()->getMousePosition();

		velocity = (vec - position) / 100;
	}

	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		velocity.setX(2);
	}
	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		velocity.setX(-2);
	}
	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_UP))
	{
		velocity.setY(-2);
	}
	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		velocity.setY(2);
	}

}