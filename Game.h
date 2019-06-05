#pragma once
#include "SDL.h"
#include "SDL_image.h"

#include <iostream>

#include "HUD.h"
#include "QTable.h"

class Game {
private:
	int windowWidth, windowHeight;

	bool isRunning = false;

	HUD* hud;

	QTable tab;

	SDL_Window *window;
	SDL_Renderer *renderer;

public:
	Game();
	~Game();

	void init(const char*, int, int, int, int, bool);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

};
