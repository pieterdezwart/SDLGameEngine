#pragma once
#include "GameObject.h"

class AnimatedGraphic : public GameObject
{
public:
	AnimatedGraphic(int x, int y, int width, int height, std::string textureID, int animSpeed) : GameObject(x, y, width, height, textureID), m_animSpeed(animSpeed)
	{};

	virtual void draw(float interpolation);
	virtual void update();
	virtual void clean();

private:
	int m_animSpeed;
};

