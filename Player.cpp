#include "Player.h"

Player::Player(const char* path, SDL_Renderer* rend, Vector2D pos, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, pos, srcW, srcH, scale, n) {
	
}

Player::Player(const char* path, SDL_Renderer* rend, int x, int y, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, x, y, srcW, srcH, scale, n) {
	
}

Player::~Player() {

}

void Player::move(Vector2D mov) {
	setPos(getPos() + mov);

}

void Player::subLives() {
	lives--;
}

void Player::addLives() {
	if (lives < 20)
		lives++;
}

int Player::getLives() {
	return lives;
}

void Player::onCollision() {

}