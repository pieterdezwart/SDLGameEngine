#include "MenuState.h"
#include <iostream>
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
 
const std::string MenuState::menuID = "MENU";

void MenuState::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}

}

void MenuState::render(float interpolation)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw(interpolation);
	}

}

bool MenuState::onEnter()
{
	if (!TextureManager::getInstance()->load("Assets/menu_start.png", "playbutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::getInstance()->load("Assets/menu_exit.png", "exitbutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(100, 100, 100, 14, "playbutton");
	GameObject* button2 = new MenuButton(100, 150, 100, 14, "exitbutton");
	
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);

	std::cout << "Entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->clean();
	}

	gameObjects.clear();

	TextureManager::getInstance()->clearFromTextureMap("playbutton");
	TextureManager::getInstance()->clearFromTextureMap("exitbutton");

	std::cout << "Exiting MenuState\n";
	return true;
}