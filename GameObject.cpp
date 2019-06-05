#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* rend, Vector2D vec, int srcW, int srcH, int scale, std::string n) {
	renderer = rend;
	objTexture = TextureManager::loadTexture(textureSheet, rend);

	pos = vec;

	dimensions.x = srcW * scale;
	dimensions.y = srcH * scale;

	srcRect.w = srcW;
	srcRect.h = srcH;
	srcRect.x = srcRect.y = 0;

	dstRect.w = srcRect.w * scale;
	dstRect.h = srcRect.h * scale;

	name = n;

	//std::cout << "GameObject " << name << " created" << std::endl;
}

GameObject::GameObject(const char* textureSheet, SDL_Renderer* rend, int xpos, int ypos, int srcW, int srcH, int scale, std::string n) {
	renderer = rend;
	objTexture = TextureManager::loadTexture(textureSheet, rend);

	pos.x = xpos;
	pos.y = ypos;

	dimensions.x = srcW * scale;
	dimensions.y = srcH * scale;

	srcRect.w = srcW;
	srcRect.h = srcH;
	srcRect.x = srcRect.y = 0;

	dstRect.w = srcRect.w * scale;
	dstRect.h = srcRect.h * scale;

	name = n;

	//std::cout << "GameObject " << name << " created" << std::endl;
}

GameObject::~GameObject() {
	SDL_DestroyTexture(objTexture);
}

void GameObject::setPos(Vector2D newPos) {
	pos = newPos;
}

Vector2D GameObject::getPos() {
	return pos;
}

Vector2D GameObject::getDimensions() {
	return dimensions;
}

void GameObject::update() {

	dstRect.x = pos.x;
	dstRect.y = pos.y;
}

void GameObject::render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &dstRect);
}

std::string GameObject::getName() {
	return name;
}