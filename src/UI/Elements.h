#ifndef UI_ELEMENTS_H
#define UI_ELEMENTS_H

#pragma once

const int DEFAULT_WINDOW_WIDTH = 1280;
const int DEFAULT_WINDOW_HEIGHT = 720;

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

#include "Element.h"
#include "Elements/Box.h"
#include "Elements/Text.h"
#include "Elements/InteractiveText.h"
#include "Elements/Image.h"
#include "Elements/RepeatableImage.h"

#endif
