#include "PlayState.h"
#include <iostream>
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameStateMachine.h"
#include "GameOverState.h"

const std::string PlayState::playID = "PLAY";

void PlayState::update()
{
	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::getInstance()->getStateMachine()->pushState(new PauseState());
	}

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}

	if (checkCollision(gameObjects[0], gameObjects[1]))
	{
		Game::getInstance()->getStateMachine()->pushState(new GameOverState());
	}

}

void PlayState::render(float interpolation)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw(interpolation);
	}

}

bool PlayState::onEnter()
{
	if (!TextureManager::getInstance()->load("Assets/animate2.png", "animate", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	GameObject* player = new Player(500, 100, 128, 82, "animate");
	GameObject* enemy = new Enemy(100, 100, 128, 82, "animate");

	gameObjects.push_back(player);
	gameObjects.push_back(enemy);

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->clean();
	}

	gameObjects.clear();

	TextureManager::getInstance()->clearFromTextureMap("animate");

	std::cout << "exiting PlayState\n";
	return true;
}

bool PlayState::checkCollision(GameObject* obj1, GameObject* obj2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = obj1->getPosition().getX();
	rightA = obj1->getPosition().getX() + obj1->getWidth();
	topA = obj1->getPosition().getY();
	bottomA = obj1->getPosition().getY() + obj1->getHeight();
	
	//Calculate the sides of rect B
	leftB = obj2->getPosition().getX();
	rightB = obj2->getPosition().getX() + obj2->getWidth();
	topB = obj2->getPosition().getY();
	bottomB = obj2->getPosition().getY() + obj2->getHeight();
	
	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	
	return true;
}