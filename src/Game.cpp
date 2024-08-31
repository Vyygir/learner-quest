#include "Game.h"

Game::Game(SDL_Window *window, SDL_Renderer *renderer) :
	running(false),
	fullscreen(false),
	window(window),
	renderer(renderer),
	previousTime(0),
	currentTime(0),
	lag(0) {}

void Game::update() {
	// Update game logic
}

SDL_Renderer *Game::getRenderer() {
	return renderer;
}

void Game::setPreviousTime(Uint32 time) {
	previousTime = time;
}

Uint32 Game::getPreviousTime() const {
	return previousTime;
}

void Game::setCurrentTime(Uint32 time) {
	currentTime = time;
}

Uint32 Game::getCurrentTime() const {
	return currentTime;
}

void Game::setLag(Uint32 lag) {
	this->lag = lag;
}

Uint32 Game::getLag() const {
	return this->lag;
}

void Game::setRunning(bool isRunning) {
	this->running = isRunning;
}

bool Game::isRunning() const {
	return this->running;
}

void Game::setFullscreen(bool isFullscreen) {
	this->fullscreen = isFullscreen;

	Uint32 flags = 0;

	if (this->isFullscreen()) {
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	SDL_SetWindowFullscreen(this->window, flags);
}

bool Game::isFullscreen() const {
	return this->fullscreen;
}

void Game::quit() {
	Game::setRunning(false);
}