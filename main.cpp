#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <string>
#include "DataManager.h"

Game *game = nullptr;

void play();

int main(int argc, char *argv[]) {
	char a = 'y';

	while (a == 'y' || a == 'Y') {
		play();
		system("cls");
		std::cout << "Czy chcesz zagrac jeszcze raz? (Y/N)" << std::endl;
		std::cin >> a;
		system("cls");
	}

	return 0;
}

void play() {
	game = new Game();

	const int targetFPS = 60;
	const int frameDelay = 1000 / targetFPS;

	Uint32 frameStart;
	int frameTime;

	game->init("SpaceInvaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, false);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
}