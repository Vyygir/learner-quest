#ifndef UI_H
#define UI_H

#pragma once

#include <string>
#include <map>
#include <queue>
#include <functional>
#include <mutex>
#include "SDL_ttf.h"
#include "UI/Forward/Element.h"

class Interface {
public:
	static void initialise(SDL_Renderer* renderer);
	static Interface& getInstance();
	[[nodiscard]] SDL_Renderer* getRenderer() const;

	void setBackgroundColor(SDL_Color color);

	SDL_Color getBackgroundColor();

	void addFont(const std::string &name, const std::string &fontPath);
	TTF_Font* getFont(const std::string &name, int fontSize);

	void addElementEventHandler(UI::Element *element);
	void handleElementEvents(const SDL_Event &event);

	void getWindowSize(int &width, int &height) const;
private:
	explicit Interface(SDL_Renderer *renderer);
	~Interface();

	Interface(const Interface&) = delete;
	Interface& operator = (const Interface&) = delete;

	static Interface* instance;
	static std::mutex instanceMutex;
	static bool initialised;

	SDL_Renderer *renderer;
	std::map<std::string, std::string> fonts;
	SDL_Color backgroundColor = { 0, 0, 0, 255 };

	std::vector<UI::Element*> interactiveElements;

};

#endif
