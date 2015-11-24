#pragma once
#include "GameState.h"
#include <vector>

class GameObject;

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render(float interpolation);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return gameOverID; }

private:

	static const std::string gameOverID;

	std::vector<GameObject*> gameObjects;
};

