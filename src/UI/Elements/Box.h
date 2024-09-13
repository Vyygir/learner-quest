#ifndef UI_BOX_H
#define UI_BOX_H

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "../../Utilities/Logger.h"
#include "../Element.h"

namespace UI {
	class Box : public Element {
	private:
		SDL_Color color;

	public:
		Box(
			SDL_Color color,
			Scale scale,
			Alignment alignment,
			Offset offset = Offset{ 0, 0 }
		) : Element(nullptr, {0, 0, 0, 0}, alignment, scale, offset, true), color(color) {}

		Box(
			SDL_Color color,
			Dimensions dimensions,
			Alignment alignment,
			Offset offset = Offset{ 0, 0 }
		) : Element(nullptr, {0, 0, 0, 0}, alignment, dimensions, offset, false), color(color) {}

		void render() override {
			if (!this->isVisible) {
				return;
			}

			SDL_Renderer* renderer = Interface::getInstance().getRenderer();

			this->preRender(renderer);

			SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, this->color.a);
			SDL_RenderFillRect(renderer, &this->rect);
		}

		void setColor(const SDL_Color& newColor) {
			this->color = newColor;
		}
	};
}

#endif
