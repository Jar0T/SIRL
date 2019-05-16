#pragma once
#include "AlienBullet.h"

AlienBullet::AlienBullet(const char* path, SDL_Renderer* rend, Vector2D pos, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, pos, srcW, srcH, scale, n) {

}

AlienBullet::AlienBullet(const char* path, SDL_Renderer* rend, int x, int y, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, x, y, srcW, srcH, scale, n) {

}

AlienBullet::~AlienBullet() {

}

void AlienBullet::move() {
	Vector2D down(0, 1);
	setPos(getPos() + (down * speed));

}