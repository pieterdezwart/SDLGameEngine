#include "TextureManager.h"

TextureManager* TextureManager::instance = 0;

TextureManager::~TextureManager()
{
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface == 0)
	{
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_FreeSurface(tempSurface);

	// add the texture to the map
	if (texture != nullptr)
	{
		textureMap[id] = texture;
		return true;
	}

	return false; // something went wrong
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}