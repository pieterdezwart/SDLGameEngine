#pragma once
#include "GameState.h"
#include <vector>

class GameObject;

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render(float interpolation);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return pauseID; }

private:
	static const std::string pauseID;

	std::vector<GameObject*> gameObjects;
};

