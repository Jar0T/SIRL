#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <iostream>

class AlienBullet : public GameObject {
private:
	int speed = 10;
	int lives = 3;

public:
	AlienBullet(const char*, SDL_Renderer*, Vector2D, std::string, int, int, int);
	AlienBullet(const char*, SDL_Renderer*, int, int, std::string, int, int, int);
	~AlienBullet();
	void move();

};