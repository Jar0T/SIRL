#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <iostream>

class PlayerBullet : public GameObject {
private:
	int speed = 10;

public:
	PlayerBullet(const char*, SDL_Renderer*, Vector2D, std::string, int, int, int);
	PlayerBullet(const char*, SDL_Renderer*, int, int, std::string, int, int, int);
	~PlayerBullet();
	void move();

};