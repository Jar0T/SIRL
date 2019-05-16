#include "HUD.h"
#include "TextureManager.h"
#include <string>
#include <sstream>

int nextRow = 10;

HUD::HUD(SDL_Renderer* rend, int width, int height) {
	healthTexture = TextureManager::loadTexture("Assets/Heart.png", rend);

	if (TTF_Init() < 0)
		std::cout << "Error: " << TTF_GetError() << std::endl;

	renderer = rend;

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	dstRect.w = srcRect.w;
	dstRect.h = srcRect.h;

	font = TTF_OpenFont("Assets/advanced_pixel-7.ttf", 20);
	color = { 255, 255, 255 };

	scoreRect.h = 32;
	scoreRect.y = 5;

	waveRect.h = 32;
	waveRect.y = 5;

	multRect.h = 32;
	multRect.y = waveRect.y + waveRect.h + 5;

	w = width;
	h = height;

}

void HUD::renderLives(int lives) {
	for (int i = 0; i < lives; i++) {
		if (i >= nextRow) {
			dstRect.y += 37;
			nextRow += 10;
		}

		dstRect.x = dstRect.w * (i - (nextRow - 10)) + 5;
		SDL_RenderCopy(renderer, healthTexture, &srcRect, &dstRect);
	}

	nextRow = 10;
	dstRect.y = 0;
}

void HUD::renderScore() {
	scoreRect.w = std::strlen(std::to_string(DataManager::score).c_str()) * 20;
	scoreRect.x = w - scoreRect.w;

	scoreSurface = TTF_RenderText_Solid(font, std::to_string(DataManager::score).c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	SDL_RenderCopy(renderer, texture, NULL, &scoreRect);
}

void HUD::renderWave() {
	std::stringstream ss;
	std::string s;

	ss << "Wave: " << std::to_string(DataManager::waves);
	s = ss.str();

	waveRect.w = std::strlen(s.c_str()) * 20;
	waveRect.x = (w / 2) - (waveRect.w / 2);

	waveSurface = TTF_RenderText_Solid(font, s.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, waveSurface);
	SDL_RenderCopy(renderer, texture, NULL, &waveRect);
}

void HUD::renderMultiplier() {
	std::stringstream ss;
	std::string s;

	ss << "Multiplier: x" << std::to_string(DataManager::multiplier);
	s = ss.str();

	multRect.w = std::strlen(s.c_str()) * 20;
	multRect.x = (w / 2) - (multRect.w / 2);

	multSurface = TTF_RenderText_Solid(font, s.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, multSurface);
	SDL_RenderCopy(renderer, texture, NULL, &multRect);
}

void HUD::renderPresence() {
	for (int i = 0; i < 9; i++) {
		std::stringstream ss;
		std::string s;

		switch (i) {
		case 0:
			ss << "LA " << (DataManager::leftAlien == true ? "TRUE" : "FALSE");
			s = ss.str();
			break;
		case 1:
			ss << "MA " << (DataManager::middleAlien == true ? "TRUE" : "FALSE");
			s = ss.str();
			break;
		case 2:
			ss << "RA " << (DataManager::rightAlien == true ? "TRUE" : "FALSE");
			s = ss.str();
			break;
		case 3:
			ss << "LB " << (DataManager::leftBullet == true ? "TRUE" : "FALSE");
			s = ss.str();
			break;
		case 4:
			ss << "MB " << (DataManager::middleBullet == true ? "TRUE" : "FALSE");
			s = ss.str();
			break;
		case 5:
			ss << "RB " << (DataManager::rightBullet == true ? "TRUE" : "FALSE");
			s = ss.str();
			break;
		case 6:
			ss << "LFB " << (DataManager::LFBullet == true ? "TRUE" : "FALSE");
			s = ss.str();
			break;
		case 7:
			ss << "MFB " << (DataManager::MFBullet == true ? "TRUE" : "FALSE");
			s = ss.str();
			break;
		case 8:
			ss << "RFB " << (DataManager::RFBullet == true ? "TRUE" : "FALSE");
			s = ss.str();
			break;
		}

		prRect.w = std::strlen(s.c_str()) * 15;
		prRect.h = 20;
		prRect.x = 20;
		prRect.y = 700 - 11 * i;

		prSurface = TTF_RenderText_Solid(font, s.c_str(), color);
		texture = SDL_CreateTextureFromSurface(renderer, prSurface);
		SDL_RenderCopy(renderer, texture, NULL, &prRect);
	}
}

void HUD::render(int lives) {
	renderLives(lives);
	renderScore();
	renderWave();
	renderMultiplier();
	renderPresence();

}