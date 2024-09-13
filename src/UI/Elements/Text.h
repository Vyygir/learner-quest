#ifndef UI_TEXT_H
#define UI_TEXT_H

#pragma once

#include "SDL.h"
//#include "../../Options.h"
#include "../../Utilities/Logger.h"
#include "../Element.h"

namespace UI {
	class Text : public Element {
	private:
		const std::string fontName;
		int normalSize;
		int fontSize;
		bool scaleFont;

		void createFont() {
			int size = this->fontSize ? this->fontSize : this->normalSize;

			this->font = Interface::getInstance().getFont(fontName, size);
		}

	protected:
		TTF_Font* font;
		std::string content;
		SDL_Color color;

		SDL_Texture* createTexture() {
			if (!this->font) {
				Logger::warn("Font was not present:\n\t" + std::string(TTF_GetError()));
				return nullptr;
			}

			SDL_Surface *surface = TTF_RenderText_Blended(this->font, this->content.c_str(), this->color);

			if (!surface) {
				Logger::warn("Failed to render text: \n\tContent: \"" + this->content + "\"\n\tError:   " + SDL_GetError());
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
			Offset offset = { 0, 0 },
			bool scaleFont = false
		) : Element(nullptr, {0, 0, 0, 0}, alignment, Scale{ 1.0f, 1.0f }, offset, false),
			fontName(fontName),
			content(content),
			normalSize(fontSize),
			fontSize(fontSize),
			color(color),
			scaleFont(scaleFont)
		{
			this->createFont();
		}

		void render() override {
			if (this->scaleFont) {
				int windowWidth, windowHeight;
				Interface::getInstance().getWindowSize(windowWidth, windowHeight);

				if (windowWidth != this->previousWindowSize.w || windowHeight != this->previousWindowSize.h) {
					this->previousWindowSize = { windowWidth, windowHeight };
					this->fontSize = (this->normalSize * windowWidth) / DEFAULT_WINDOW_WIDTH;

					this->createFont();

					this->setOffset({
						(this->normalOffset.x * windowWidth) / DEFAULT_WINDOW_WIDTH,
						(this->normalOffset.y * windowHeight / DEFAULT_WINDOW_HEIGHT)
					});
				}
			}

			this->texture = createTexture();

			if (this->texture) {
				int w, h;

				SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

				this->rect.w = w;
				this->rect.h = h;
			}

			Element::render();
		}
	};
}

#endif