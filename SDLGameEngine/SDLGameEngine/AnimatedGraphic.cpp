#include "AnimatedGraphic.h"

void AnimatedGraphic::draw(float interpolation)
{
	GameObject::draw(interpolation);
}

void AnimatedGraphic::update()
{
	currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % 2));
}

void AnimatedGraphic::clean()
{

}
