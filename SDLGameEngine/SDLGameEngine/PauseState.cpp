#include "PauseState.h"
#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "InputHandler.h"

const std::string PauseState::pauseID = "PAUSE";

void PauseState::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}
void PauseState::render(float interpolation)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw(interpolation);
	}
}

bool PauseState::onEnter()
{
	if (!TextureManager::getInstance()->load("Assets/pause_resume.png", "resumebutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	if (!TextureManager::getInstance()->load("Assets/pause_mainmenu.png", "mainbutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(200, 100, 128, 14, "mainbutton");
	GameObject* button2 = new MenuButton(200, 300, 128, 14, "resumebutton");

	gameObjects.push_back(button1);
	gameObjects.push_back(button2);

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->clean();
	}

	gameObjects.clear();

	TextureManager::getInstance()->clearFromTextureMap("mainbutton");
	TextureManager::getInstance()->clearFromTextureMap("resumebutton");

	// reset the mouse button states to false
	//InputHandler::getInstance()->reset();

	std::cout << "Exiting MenuState\n";
	return true;
}