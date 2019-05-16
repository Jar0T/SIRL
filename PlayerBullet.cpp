#include "PlayeBullet.h"

PlayerBullet::PlayerBullet(const char* path, SDL_Renderer* rend, Vector2D pos, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, pos, srcW, srcH, scale, n) {
	
}

PlayerBullet::PlayerBullet(const char* path, SDL_Renderer* rend, int x, int y, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, x, y, srcW, srcH, scale, n) {
	
}

PlayerBullet::~PlayerBullet() {

}

void PlayerBullet::move() {
	Vector2D up(0, -1);
	setPos(getPos() + (up * speed));

}