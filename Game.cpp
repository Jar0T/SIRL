#include <array>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Game.h"
#include "TextureManager.h"
#include "Alien.h"
#include "Player.h"
#include "Counter.h"
#include "PlayeBullet.h"
#include "AlienBullet.h"
#include "HUD.h"
#include "DataManager.h"
#include "UFO.h"

#define middleAlien DataManager::middleAlien
#define leftAlien DataManager::leftAlien
#define rightAlien DataManager::rightAlien
#define middleBullet DataManager::middleBullet
#define leftBullet DataManager::leftBullet
#define rightBullet DataManager::rightBullet
#define RFBullet DataManager::RFBullet
#define MFBullet DataManager::MFBullet
#define LFBullet DataManager::LFBullet

bool middleAlien = false;
bool leftAlien = false;
bool rightAlien = false;
bool middleBullet = false;
bool leftBullet = false;
bool rightBullet = false;
bool RFBullet = false;
bool MFBullet = false;
bool LFBullet = false;

int DataManager::score = 0;
int DataManager::level = 0;
int DataManager::nextLevel = 2;
int DataManager::waves = 0;
int DataManager::maxLevel = 5;
int DataManager::multiplier = 1;
int DataManager::aliensKilled = 0;
int DataManager::nextLive = 50000;
int DataManager::multThr = 10;
int DataManager::maxMult = 5;

clock_t start;

Counter c1(60); //Counter to determine if aliens can already move
Counter c2(600); //Counter to determine if UFO should be spawned

std::vector<Alien*> alien; //Array of aliens
Player* player; //Pointer to player object
UFO* ufo; //Pointer to ufo object

std::vector<PlayerBullet*> pBullet; //Vector of player bullets
std::vector<AlienBullet*> aBullet; //Vector of alien bullets

Vector2D right(1, 0), down(0, 1); //2D vectors for moving right and down

int alienSpeed = 20;
int playerSpeed = 0;
int ufoSpeed = 15;

int playerMaxB = 3;

int threshold = 10;

int scale = 2;

bool moveDown = false, LRMovement = true; //Can aliens move down and are they moving left or right?

//Are Aliens/Bullets present on right, left or in the middle
int presence() {
	int a = 0;

	middleAlien = false;
	leftAlien = false;
	rightAlien = false;
	middleBullet = false;
	leftBullet = false;
	rightBullet = false;
	RFBullet = false;
	MFBullet = false;
	LFBullet = false;

	for (int i = 0; i < alien.size(); i++) {
		if (alien[i]->getPos().x <= player->getPos().x) {
			leftAlien = true;
		}
		if (alien[i]->getPos().x >= player->getPos().x && alien[i]->getPos().x <= player->getPos().x + player->getDimensions().x) {
			middleAlien = true;
		}
		if (alien[i]->getPos().x >= player->getPos().x + player->getDimensions().x) {
			rightAlien = true;
		}
	}

	for (int i = 0; i < aBullet.size(); i++) {
		if (aBullet[i]->getPos().x >= player->getPos().x - player->getDimensions().x && aBullet[i]->getPos().x < player->getPos().x) {
			leftBullet = true;
		}
		if (aBullet[i]->getPos().x >= player->getPos().x && aBullet[i]->getPos().x <= player->getPos().x + player->getDimensions().x) {
			middleBullet = true;
		}
		if (aBullet[i]->getPos().x >= player->getPos().x + player->getDimensions().x && aBullet[i]->getPos().x <= player->getPos().x + 2 * player->getDimensions().x) {
			rightBullet = true;
		}
	}

	for (int i = 0; i < aBullet.size(); i++) {
		if (aBullet[i]->getPos().x >= player->getPos().x - player->getDimensions().x && 
			aBullet[i]->getPos().x < player->getPos().x && 
			aBullet[i]->getPos().y >= player->getPos().y - 64 &&
			aBullet[i]->getPos().y + aBullet[i]->getDimensions().y <player->getPos().y) {
			LFBullet = true;
		}
		if (aBullet[i]->getPos().x >= player->getPos().x && 
			aBullet[i]->getPos().x <= player->getPos().x + player->getDimensions().x &&
			aBullet[i]->getPos().y >= player->getPos().y - 64 &&
			aBullet[i]->getPos().y + aBullet[i]->getDimensions().y < player->getPos().y + player->getDimensions().y) {
			MFBullet = true;
		}
		if (aBullet[i]->getPos().x >= player->getPos().x + player->getDimensions().x && 
			aBullet[i]->getPos().x <= player->getPos().x + 2 * player->getDimensions().x &&
			aBullet[i]->getPos().y >= player->getPos().y - 64 &&
			aBullet[i]->getPos().y + aBullet[i]->getDimensions().y < player->getPos().y) {
			RFBullet = true;
		}
	}

	if (leftAlien)
		a = a | 1;
	a = a << 1;
	if (middleAlien)
		a = a | 1;
	a = a << 1;
	if (rightAlien)
		a = a | 1;
	a = a << 1;
	if (leftBullet)
		a = a | 1;
	a = a << 1;
	if (middleBullet)
		a = a | 1;
	a = a << 1;
	if (rightBullet)
		a = a | 1;
	a = a << 1;
	if (LFBullet)
		a = a | 1;
	a = a << 1;
	if (MFBullet)
		a = a | 1;
	a = a << 1;
	if (RFBullet)
		a = a | 1;

	return a;
}

//Spawns 55 aliens in 5x11 grid
void spawnAliens(SDL_Renderer *rend) {
	while (pBullet.size() > 0) {
		delete(pBullet[0]);
		pBullet.erase(pBullet.begin());
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			alien.push_back(new Alien("Assets/Alien.png", rend, (j * 64) + 10, (i * 64) + 150, "Alien", 32, 32, scale));
		}
	}

	if (alienSpeed < 0)
		alienSpeed *= -1;

	DataManager::waves++;
	if (DataManager::waves > DataManager::nextLevel) {
		DataManager::nextLevel += 2;
		if (DataManager::level < DataManager::maxLevel) {
			DataManager::level++;
		}
	}
}

//Checks if alien collides with bullet
void collisionAB() {
	for (int i = 0; i < pBullet.size(); i++) {
		for (int j = 0; j < alien.size(); j++) {
			if (pBullet[i]->getPos().x + pBullet[i]->getDimensions().x >= alien[j]->getPos().x &&
				alien[j]->getPos().x + alien[j]->getDimensions().x >= pBullet[i]->getPos().x &&
				pBullet[i]->getPos().y + pBullet[i]->getDimensions().y >= alien[j]->getPos().y &&
				alien[j]->getPos().y + alien[j]->getDimensions().y >= pBullet[i]->getPos().y) {

				alien[j]->onCollision();
				delete(pBullet[i]);
				pBullet.erase(pBullet.begin() + i);
				delete(alien[j]);
				alien.erase(alien.begin() + j);
				i--;
				j--;

				DataManager::aliensKilled++;
				if (DataManager::aliensKilled > DataManager::multThr) {
					if (DataManager::multiplier < DataManager::maxMult) {
						DataManager::multiplier++;
						DataManager::multThr *= 3;
					}
				}
				else if (DataManager::aliensKilled < 10) {
					DataManager::multiplier = 1;
					DataManager::multThr = 10;
				}

				break;
			}
		}
	}
}

//Checks if player collides with bullet
bool collisionPB() {
	for (int i = 0; i < aBullet.size(); i++) {
		if (aBullet[i]->getPos().x + aBullet[i]->getDimensions().x >= player->getPos().x &&
			player->getPos().x + player->getDimensions().x >= aBullet[i]->getPos().x &&
			aBullet[i]->getPos().y + aBullet[i]->getDimensions().y >= player->getPos().y &&
			player->getPos().y + player->getDimensions().y >= aBullet[i]->getPos().y) {
			
			player->subLives();
			delete(aBullet[i]);
			aBullet.erase(aBullet.begin() + i);

			DataManager::aliensKilled = 0;

			return true;
		}
	}
	return false;
}

//Checks if UFO collides with bullet
//void collisionUB() {
//	for (int i = 0; i < pBullet.size(); i++) {
//		if (pBullet[i]->getPos().x + pBullet[i]->getDimensions().x >= ufo->getPos().x &&
//			ufo->getPos().x + ufo->getDimensions().x >= pBullet[i]->getPos().x &&
//			pBullet[i]->getPos().y + pBullet[i]->getDimensions().y >= ufo->getPos().y &&
//			ufo->getPos().y + ufo->getDimensions().y >= pBullet[i]->getPos().y) {
//
//			ufo->onCollision();
//			delete(pBullet[i]);
//			pBullet.erase(pBullet.begin() + i);
//			delete(ufo);
//			ufo = nullptr;
//
//			break;
//		}
//	}
//}

Game::Game() {

}

Game::~Game() {

}

#pragma region initialization
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	srand(time(NULL));

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout <<"Initialised!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			std::cout << "Window created!" << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	windowWidth = width;
	windowHeight = height;

	tab.init(0.01, 0.8, 512);

	hud = new HUD(renderer, width, height);

	spawnAliens(renderer);

	player = new Player("Assets/Player.png", renderer, width / 2 - 32, height - 80, "Player", 32, 32, scale);

}
#pragma endregion

#pragma region events_handling
void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) {
		isRunning = false;
	}

	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			isRunning = false;
		/*case SDLK_LEFT:
			playerSpeed = -10;
			break;
		case SDLK_RIGHT:
			playerSpeed = 10;
			break;
		case SDLK_SPACE:
			if (pBullet.size() < playerMaxB) {
				pBullet.push_back(new PlayerBullet("Assets/Player_Bullet.png", renderer, player->getPos().x + 32, player->getPos().y, "pBullet", 2, 6, scale));
			}
			break;*/
		default:
			break;
		}
	}

	/*if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			playerSpeed = 0;
			break;
		case SDLK_RIGHT:
			playerSpeed = 0;
			break;
		default:
			break;
		}
	}*/

}
#pragma endregion

#pragma region update
void Game::update() {
	int lastScore = DataManager::score;
	bool tooLow = false;

	for (auto &v : alien) {
		if ((v->getPos().x >= (windowWidth - 64) || v->getPos().x <= 0) && moveDown) {
			alienSpeed *= (-1);
			moveDown = false;
			LRMovement = false;
			for (auto &a : alien) {
				a->move(down * 32);
				if (a->getPos().y > (windowHeight - (70 + a->getDimensions().y)))
					tooLow = true;
			}
			break;
		}
	}
	
	if (c1.getValue() == 0 && LRMovement) {
		for (auto &v : alien) {
			v->move(right * alienSpeed);
			if (rand() % 100 < threshold && aBullet.size() <= 2 + DataManager::level) {
				aBullet.push_back(new AlienBullet("Assets/Alien_Bullet.png", renderer, v->getPos().x + 32, v->getPos().y, "aBllet", 4, 8, scale));
			}
		}
		moveDown = true;
	}

	for (auto &v : alien) {
		v->update();
	}

	/*if (c2.getValue() == 0) {
		if (rand() % 2 > 1) {
			ufo = new UFO("Assets/UFO.png", renderer, windowWidth + 10, 90, "UFO", 64, 32, scale);
			ufoSpeed = -15;
		}
		else {
			ufo = new UFO("Assets/UFO.png", renderer, -138, 90, "UFO", 64, 32, scale);
			ufoSpeed = 15;
		}
	}*/

	/*if (ufo != nullptr) {
		ufo->move(right * ufoSpeed);
		ufo->update();
		if (ufo->getPos().x < -(ufo->getDimensions().x + 10)) {
			delete(ufo);
			ufo = nullptr;
		}
		collisionUB();
	}*/

	//presence();

	int a = presence();

	a = tab.getAction(a);

	switch (a) {
	case 0:
		playerSpeed = -10;
		break;
	case 1:
		playerSpeed = 10;
		break;
	case 2:
		if (pBullet.size() < playerMaxB) {
			pBullet.push_back(new PlayerBullet("Assets/Player_Bullet.png", renderer, player->getPos().x + 32, player->getPos().y, "pBullet", 2, 6, scale));
		}
		break;
	case 3:
		playerSpeed = 0;
		break;
	case 4:
		playerSpeed = -10;
		if (pBullet.size() < playerMaxB) {
			pBullet.push_back(new PlayerBullet("Assets/Player_Bullet.png", renderer, player->getPos().x + 32, player->getPos().y, "pBullet", 2, 6, scale));
		}
		break;
	case 5:
		playerSpeed = 10;
		if (pBullet.size() < playerMaxB) {
			pBullet.push_back(new PlayerBullet("Assets/Player_Bullet.png", renderer, player->getPos().x + 32, player->getPos().y, "pBullet", 2, 6, scale));
		}
		break;
	default:
		break;
	}

	if ((player->getPos().x <= 10 && playerSpeed < 0) || (player->getPos().x >= windowWidth - 74 && playerSpeed > 0))
		playerSpeed = 0;

	if (playerSpeed != 0)
		player->move(right * playerSpeed);
	player->update();

	for (int i = 0; i < pBullet.size(); i++) {
		pBullet[i]->move();
		pBullet[i]->update();
		if (pBullet[i]->getPos().y < 0 - 10) {
			delete(pBullet[i]);
			pBullet.erase(pBullet.begin() + i);
		}
	}

	for (int i = 0; i < aBullet.size(); i++) {
		aBullet[i]->move();
		aBullet[i]->update();
		if (aBullet[i]->getPos().y > windowHeight + 10) {
			delete(aBullet[i]);
			aBullet.erase(aBullet.begin() + i);
		}
	}

	collisionAB();
	//collisionPB();

	bool gotHit = false;
	
	if (collisionPB())
		gotHit = true;

	if (DataManager::score >= DataManager::nextLive) {
		player->addLives();
		DataManager::nextLive += 50000;
	}

	if (player->getLives() <= 0)
		player->addLives();

	LRMovement = true;

	if (DataManager::score - lastScore != 0) {
		tab.reward((DataManager::score - lastScore) / 100.0);
		start = clock();
	}
	else {
		if (!((leftAlien && playerSpeed == -10) || (rightAlien && playerSpeed == 10)))
			tab.reward((clock() - start) / CLOCKS_PER_SEC);
	}

	if (middleBullet == true)
		tab.reward(-5.0);

	if (MFBullet == true)
		tab.reward(-10.0);

	if (gotHit == true)
		tab.reward(-100.0);

	if (tooLow == true)
		alien.clear();

	if (alien.size() == 0) {
		spawnAliens(renderer);
	}

	playerSpeed = 0;
}
#pragma endregion

#pragma region render
void Game::render() {
	SDL_RenderClear(renderer);

	for (auto &v : alien) {
		v->render();
	}

	for (auto &v : pBullet) {
		v->render();
	}

	for (auto &v : aBullet) {
		v->render();
	}

	/*if (ufo != nullptr) {
		ufo->render();
	}*/

	player->render();

	hud->render(player->getLives());

	SDL_RenderPresent(renderer);
}
#pragma endregion

#pragma region clean_after_game
void Game::clean() {
	tab.saveTab();

	while (alien.size() > 0) {
		delete(alien[0]);
		alien.erase(alien.begin());
	}

	while (pBullet.size() > 0) {
		delete(pBullet[0]);
		pBullet.erase(pBullet.begin());
	}

	//delete(ufo);
	delete(player);
	delete(hud);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "Game cleaned!" << std::endl;
}
#pragma endregion