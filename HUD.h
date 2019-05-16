#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "DataManager.h"

class HUD {
private:
	SDL_Texture* healthTexture;
	SDL_Texture* texture;

	SDL_Rect srcRect, dstRect, scoreRect, waveRect, multRect, prRect;
	SDL_Renderer* renderer;

	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* scoreSurface, *waveSurface, *multSurface, *prSurface;

	int w;
	int h;

	void renderLives(int);
	void renderScore();
	void renderWave();
	void renderMultiplier();
	void renderPresence();

public:
	HUD(SDL_Renderer*, int, int);

	void render(int);
};