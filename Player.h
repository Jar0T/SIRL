#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <iostream>

class Player : public GameObject {
private:
	int lives = 3;
	int maxLives = 20;

public:
	Player(const char*, SDL_Renderer*, Vector2D, std::string, int, int, int);
	Player(const char*, SDL_Renderer*, int, int, std::string, int, int, int);
	~Player();
	void move(Vector2D);

	void subLives();
	void addLives();

	int getLives();

	void onCollision();

};