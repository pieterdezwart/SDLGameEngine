#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <map>

class TextureManager
{
private:
	TextureManager() {};

	static TextureManager* instance;

	std::map<std::string, SDL_Texture*> textureMap;

public:
	static TextureManager* getInstance()
	{
		if (instance == 0)
		{
			instance = new TextureManager();
			return instance;
		}
		return instance;
	}

	~TextureManager();

	bool load(std::string fileName, std::string id, SDL_Renderer* renderer);

	// draw single image
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// draw frame
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void clearFromTextureMap(std::string id);
};

