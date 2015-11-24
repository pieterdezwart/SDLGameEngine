#include "GameOverState.h"
#include "TextureManager.h"
#include "Game.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"

const std::string GameOverState::gameOverID = "GAMEOVER";

void GameOverState::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}
void GameOverState::render(float interpolation)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw(interpolation);
	}
}

bool GameOverState::onEnter()
{
	if (!TextureManager::getInstance()->load("Assets/gameover.png", "gameovertext", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	if (!TextureManager::getInstance()->load("Assets/pause_mainmenu.png", "mainbutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	if (!TextureManager::getInstance()->load("Assets/gameover_restart.png", "restartbutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	GameObject* gameOverText = new AnimatedGraphic(200, 100, 190, 30, "gameovertext", 2);
	GameObject* button1 = new MenuButton(200, 200, 128, 14, "mainbutton");
	GameObject* button2 = new MenuButton(200, 300, 128, 14, "restartbutton");

	gameObjects.push_back(gameOverText);
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);

	std::cout << "entering GameOverState\n";
	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->clean();
	}

	gameObjects.clear();

	TextureManager::getInstance()->clearFromTextureMap("gameovertext");
	TextureManager::getInstance()->clearFromTextureMap("mainbutton");
	TextureManager::getInstance()->clearFromTextureMap("restartbutton");

	// reset the mouse button states to false
	//InputHandler::getInstance()->reset();

	std::cout << "Exiting GameOverState\n";
	return true;
}