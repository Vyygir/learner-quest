#ifndef UI_H
#define UI_H

#include <string>
#include <map>
#include <queue>
#include <functional>
#include <mutex>
#include "SDL_ttf.h"

struct Dimensions {
	int w = -1;
	int h = -1;
};

struct Scale {
	float x = 1.0f;
	float y = 1.0f;
};

struct Offset {
	int x;
	int y;
};

enum class HorizontalAlignment {
	Left,
	Center,
	Right,
};

enum class VerticalAlignment {
	Top,
	Center,
	Bottom,
};

struct Alignment {
	HorizontalAlignment x;
	VerticalAlignment y;
};

struct UIElement {
	SDL_Texture *texture;
	SDL_Rect rect;
	Offset offset;
	bool repeatX;
	bool repeatY;
};

struct InteractiveElement {
	UIElement element;
	std::function<void()> onClick;
	std::string fontName;
	std::string text;
	int fontSize;
	SDL_Color color;
	SDL_Color hoverColor;
	bool isHovered;
	bool isClicked;
};

class Interface {
public:
	static void initialise(SDL_Renderer* renderer);
	static Interface& getInstance();
	[[nodiscard]] SDL_Renderer* getRenderer() const;

	void setBackgroundColor(SDL_Color color);

	SDL_Color getBackgroundColor();

	void addFont(const std::string &name, const std::string &fontPath);
	TTF_Font* getFont(const std::string &name, int fontSize);

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
	std::queue<UIElement> queue;
	std::queue<InteractiveElement*> interactiveQueue;
	SDL_Color backgroundColor = { 0, 0, 0, 255 };

	void getWindowSize(int &width, int &height) const;
};

#endif
