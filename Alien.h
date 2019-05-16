#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <iostream>
#include <string>

class Alien : public GameObject {
private:

public:
	Alien(const char*, SDL_Renderer*, Vector2D, std::string, int, int, int);
	Alien(const char*, SDL_Renderer*, int, int, std::string, int, int, int);
	~Alien();
	void move(Vector2D);

	void onCollision();

};
