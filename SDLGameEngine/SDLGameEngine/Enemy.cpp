#include "Enemy.h"


void Enemy::draw(float interpolation)
{
	GameObject::draw(interpolation);
}

void Enemy::update()
{
	currentFrame = int(((SDL_GetTicks() / 100) % 6));

	int ticks = SDL_GetTicks();

	position.setX(position.getX() + 1);
	position.setY(position.getY() + 1);
}

void Enemy::clean()
{

}
