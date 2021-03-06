#pragma once
#include "GameState.h"
#include <vector>

class GameObject;

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render(float interpolation);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return playID; }

private:

	static const std::string playID;

	std::vector<GameObject*> gameObjects;

	bool checkCollision(GameObject* obj1, GameObject* obj2);
};

