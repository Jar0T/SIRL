#include "Alien.h"
#include "DataManager.h"

Alien::Alien(const char* path, SDL_Renderer* rend, Vector2D pos, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, pos, srcW, srcH, scale, n) {
	
}

Alien::Alien(const char* path, SDL_Renderer* rend, int x, int y, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, x, y, srcW, srcH, scale, n) {
	
}

Alien::~Alien() {
	
}

void Alien::move(Vector2D mov) {
	setPos(getPos() + mov);
	
}

void Alien::onCollision() {
	DataManager::score += 100 * DataManager::multiplier;
}