#pragma once
#include "GameState.h"
#include <vector>

class GameObject;

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render(float interpolation);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return menuID; }

private:
	static const std::string menuID;

	std::vector<GameObject*> gameObjects;
};

