#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Utilities/Logger.h"
#include "Interface.h"

Interface* Interface::instance = nullptr;
std::mutex Interface::instanceMutex;
bool Interface::initialised = false;

void Interface::initialise(SDL_Renderer* renderer) {
	std::lock_guard<std::mutex> lock(instanceMutex);

	if (!instance) {
		instance = new Interface(renderer);
		initialised = true;
	}
}

Interface& Interface::getInstance() {
	std::lock_guard<std::mutex> lock(instanceMutex);

	if (!initialised) {
		Logger::error("Interface has not been initialised yet");
	}

	return *instance;
}

SDL_Renderer* Interface::getRenderer() const {
	return this->renderer;
}

Interface::Interface(SDL_Renderer* renderer) : renderer(renderer) {
	if (TTF_Init() != 0) {
		Logger::error("Wasn't able to initialise TTF_Font: " + std::string(TTF_GetError()));
	}

	if (IMG_Init(IMG_INIT_PNG) != 0) {
		Logger::error("Wasn't able to initialise SDL2_image: " + std::string(IMG_GetError()));
	}
}

void Interface::setBackgroundColor(SDL_Color color) {
	this->backgroundColor = color;
}

SDL_Color Interface::getBackgroundColor() {
	return this->backgroundColor;
}

void Interface::addFont(const std::string &name, const std::string &fontPath) {
	this->fonts[name] = fontPath;
}

TTF_Font* Interface::getFont(const std::string &name, int fontSize) {
	if (this->fonts.find(name) == this->fonts.end()) {
		return nullptr;
	}

	TTF_Font *font = TTF_OpenFont(this->fonts[name].c_str(), fontSize);

	return font;
}

void Interface::getWindowSize(int &width, int &height) const {
	SDL_Window *window = SDL_RenderGetWindow(this->renderer);

	if (!window) {
		Logger::error("Couldn't get window from renderer.");
		return;
	}

	SDL_GetWindowSize(window, &width, &height);
}
