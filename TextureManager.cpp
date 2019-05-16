#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* fileName, SDL_Renderer* rend) {
	SDL_Surface* surface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);

	return texture;
}