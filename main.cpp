//#include "SDL_main.h"
#include "SDL.h"
#include "Game.h"
//#include <fstream>
#include <iostream>
#include <string>
#include "DataManager.h"

Game *game = nullptr;

//void menu(int tab1[], std::string tab2[]);
//void printMenu();
void play();
//void checkScore(int tab1[], std::string tab2[]);
//void printInst();
//void printTop(int tab1[], std::string tab2[]);

int main(int argc, char *argv[]) {
	/*int bestScore[10] = { 0,0,0,0,0,0,0,0,0,0 };
	std::string bestName[10];

	std::fstream top;
	top.open("top_10.txt", std::ios::in);
	if (top.is_open()) {
		for (int i = 0; i < 10 && !top.eof(); i++) {
			top >> bestScore[i] >> bestName[i];
		}
	}
	top.close();

	menu(bestScore, bestName);

	top.open("top_10.txt", std::ios::out);
	for (int i = 0; i < 10; i++) {
		top << bestScore[i] << std::endl;
		top << bestName[i] << std::endl;
	}
	top.close();*/

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

//void menu(int tab1[], std::string tab2[]) {
//	int i = 0;
//	while (i < 4) {
//		printMenu();
//		std::cin >> i;
//		switch (i)
//		{
//		case 1:
//			play();
//			checkScore(tab1, tab2);
//			break;
//		case 2:
//			printInst();
//			break;
//		case 3:
//			printTop(tab1, tab2);
//			break;
//		case 4:
//			system("cls");
//			std::cout << "Dziekujemy za gre!" << std::endl;
//			system("pause");
//			break;
//		default:
//			break;
//		}
//	}
//}
//
//void printMenu() {
//	system("cls");
//	std::cout << "1. Zagraj\n2. Sterowanie\n3. Top 10\n4. Wyjœcie" << std::endl;
//}

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

//void checkScore(int tab1[], std::string tab2[]) {
//	for (int i = 0; i < 10; i++) {
//		if (DataManager::score > tab1[i]) {
//			for (int j = 9; j > i; j--) {
//				tab1[j] = tab1[j - 1];
//				tab2[j] = tab2[j - 1];
//			}
//			std::string s;
//			system("cls");
//			std::cout << "Zasluzyles sie ojczyznie. Jak sie nazywasz pilocie?" << std::endl;
//			std::cin >> s;
//			tab1[i] = DataManager::score;
//			tab2[i] = s;
//			break;
//		}
//	}
//}
//
//void printInst() {
//	system("cls");
//	std::cout << "Uzywaj strzalek, aby sie poruszac.\nNacisnij spacje aby strzelic." << std::endl;
//	system("pause");
//}
//
//void printTop(int tab1[], std::string tab2[]) {
//	system("cls");
//	for (int i = 0; i < 10; i++) {
//		std::cout << i + 1 << "\t" << tab2[i] << "\t" << tab1[i] << std::endl;
//	}
//	system("pause");
//}