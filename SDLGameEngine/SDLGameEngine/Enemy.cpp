#include "Enemy.h"


void Enemy::draw(float interpolation)
{
	GameObject::draw(interpolation);
}

void Enemy::update()
{
	currentFrame = int(((SDL_GetTicks() / 100) % 6));

	if (position.getY() < 0)
	{
		velocity.setY(2);
	}
	else if (position.getY() > 400)
	{
		velocity.setY(-2);
	}
	
	GameObject::update();
}

void Enemy::clean()
{

}
