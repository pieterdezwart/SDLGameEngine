#pragma once
#include "GameState.h"

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
};

