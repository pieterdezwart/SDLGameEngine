#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"

void GameObject::draw(float interpolation)
{
	float posX = position.getX() + (velocity.getX() * interpolation);
	float posY = position.getY() + (velocity.getY() * interpolation);

	TextureManager::getInstance()->drawFrame(textureID, posX, posY, width, height, currentRow, currentFrame, Game::getInstance()->getRenderer());
}

void GameObject::update()
{
	velocity += acceleration;
	position += velocity;
}

void GameObject::clean()
{

}