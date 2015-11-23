#pragma once
#include<vector>
class GameState;

class GameStateMachine
{
public:
	void pushState(GameState* state);

	void changeState(GameState* state);

	void popState();

	void update();
	void render(float interpolation);

private:
	std::vector<GameState*> gameStates;
};

