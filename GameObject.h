#pragma once
#include <iostream>
#include <string>
#include "Game.h"
#include "Vector2D.h"

class GameObject {
private:
	std::string name;

	Vector2D pos;
	Vector2D dimensions;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, dstRect;
	SDL_Renderer* renderer;

public:
	GameObject(const char*, SDL_Renderer*, Vector2D, int, int, int, std::string);
	GameObject(const char*, SDL_Renderer*, int, int, int, int, int, std::string);
	~GameObject();

	void setPos(Vector2D);
	Vector2D getPos();
	Vector2D getDimensions();
	std::string getName();

	void update();
	void render();

};