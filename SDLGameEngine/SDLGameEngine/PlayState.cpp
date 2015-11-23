#include "PlayState.h"
#include <iostream>

const std::string PlayState::playID = "PLAY";

void PlayState::update()
{
	// nothing for now
}

void PlayState::render(float interpolation)
{
	// nothing for now
}

bool PlayState::onEnter()
{
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	std::cout << "exiting PlayState\n";
	return true;
}