#include "Player.h"

Player::Player(const char* path, SDL_Renderer* rend, Vector2D pos, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, pos, srcW, srcH, scale, n) {
	std::cout << "Player created at x: " << std::to_string(pos.x) << " y: " << std::to_string(pos.y) << std::endl;
}

Player::Player(const char* path, SDL_Renderer* rend, int x, int y, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, x, y, srcW, srcH, scale, n) {
	std::cout << "Player created at x: " << std::to_string(x) << " y: " << std::to_string(y) << std::endl;
}

Player::~Player() {
	std::cout << "Player deleted\n";
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