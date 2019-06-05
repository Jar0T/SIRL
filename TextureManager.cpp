#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* fileName, SDL_Renderer* rend) {
	try {
		if (IMG_Load(fileName) == NULL)
			throw 1;
	}
	catch (int x) {
		std::cout << "Unable to load texture" << std::endl;
		exit(x);
	}

	SDL_Surface* surface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);

	return texture;
}