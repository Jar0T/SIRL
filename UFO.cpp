#include "UFO.h"
#include "DataManager.h"

UFO::UFO(const char* path, SDL_Renderer* rend, Vector2D pos, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, pos, srcW, srcH, scale, n) {

}

UFO::UFO(const char* path, SDL_Renderer* rend, int x, int y, std::string n, int srcW, int srcH, int scale) : GameObject(path, rend, x, y, srcW, srcH, scale, n) {

}

UFO::~UFO() {

}

void UFO::move(Vector2D mov) {
	setPos(getPos() + mov);

}

void UFO::onCollision() {
	DataManager::score += 500 * DataManager::multiplier;
}