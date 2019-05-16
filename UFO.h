#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <iostream>
#include <string>

class UFO : public GameObject {
private:

public:
	UFO(const char*, SDL_Renderer*, Vector2D, std::string, int, int, int);
	UFO(const char*, SDL_Renderer*, int, int, std::string, int, int, int);
	~UFO();
	void move(Vector2D);

	void onCollision();

};