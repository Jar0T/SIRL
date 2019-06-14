#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <string>
#include "DataManager.h"

Game *game = nullptr;

void play();

int main(int argc, char *argv[]) {
	while (true)
		play();

	return 0;
}

void play() {
	game = new Game();

	game->init("SpaceInvaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, false);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	delete(game);
}