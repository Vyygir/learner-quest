#ifndef UI_TEXT_H
#define UI_TEXT_H

#pragma once

#include "SDL.h"
#include "../../Utilities/Logger.h"
#include "../Element.h"

namespace UI {
	class Text : public Element {
	private:
		TTF_Font* font;
		std::string content;
		SDL_Color color;

		SDL_Texture* createTexture() {
			SDL_Surface *surface = TTF_RenderText_Blended(this->font, this->content.c_str(), this->color);

			if (!surface) {
				Logger::warn("Failed to render text: " + this->content);
				return nullptr;
			}

			SDL_Texture *texture = SDL_CreateTextureFromSurface(Interface::getInstance().getRenderer(), surface);
			SDL_FreeSurface(surface);

			return texture;
		}

	public:
		Text(
			const std::string &fontName,
			const std::string &content,
			SDL_Color color,
			int fontSize,
			Alignment alignment,
			Scale scale = { 1.0f, 1.0f },
			Offset offset = { 0, 0 }
		) : Element(nullptr, {0, 0, 0, 0}, alignment, scale, offset, false),
			 content(content),
			 color(color)
		{
			this->font = Interface::getInstance().getFont(fontName, fontSize);
			this->texture = createTexture();

			if (texture) {
				int w, h;

				SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

				rect.w = w;
				rect.h = h;
			}
		}

		void render() override {
			if (!texture) {
				texture = createTexture();
			}

			Element::render();
		}
	};
}

#endif