#ifndef UI_INTERACTIVE_TEXT_H
#define UI_INTERACTIVE_TEXT_H

#pragma once

#include "SDL.h"
#include "../../Utilities/Logger.h"
#include "../Element.h"
#include "Text.h"

#include <utility>

namespace UI {
	class InteractiveText : public Text {
	private:
		bool isMouseOver = false;

		std::function<void(const SDL_MouseMotionEvent &, InteractiveText*)> onMouseOver;
		std::function<void(const SDL_MouseMotionEvent &, InteractiveText*)> onMouseOut;
		std::function<void(const SDL_MouseButtonEvent &, InteractiveText*)> onClick;

		void handleMouseMotion(const SDL_MouseMotionEvent &event) {
			bool inBounds = this->isWithinBounds(event.x, event.y);

			if (inBounds && this->onMouseOver && !this->isMouseOver) {
				this->onMouseOver(event, this);
				this->isMouseOver = true;
			} else if (!inBounds && this->onMouseOut && this->isMouseOver) {
				this->onMouseOut(event, this);
				this->isMouseOver = false;
			}
		}

		void handleMouseClick(const SDL_MouseButtonEvent &event) {
			if (this->isWithinBounds(event.x, event.y) && this->onClick) {
				this->onClick(event, this);
			}
		}

	public:
		InteractiveText(
			const std::string &fontName,
			const std::string &content,
			SDL_Color color,
			int fontSize,
			Alignment alignment,
			Offset offset = { 0, 0 },
			bool scaleFont = false
		) : Text(fontName, content, color, fontSize, alignment, offset, scaleFont) {}

		void handleEvent(const SDL_Event &event) override {
			switch (event.type) {
				case SDL_MOUSEMOTION:
					this->handleMouseMotion(event.motion);
					break;

				case SDL_MOUSEBUTTONDOWN:
					this->handleMouseClick(event.button);
					break;
			}
		}

		void addMouseOverEvent(std::function<void(const SDL_MouseMotionEvent &, InteractiveText*)> callback) {
			this->onMouseOver = std::move(callback);
		}

		void addMouseOutEvent(std::function<void(const SDL_MouseMotionEvent &, InteractiveText*)> callback) {
			this->onMouseOut = std::move(callback);
		}

		void addClickEvent(std::function<void(const SDL_MouseButtonEvent &, InteractiveText*)> callback) {
			this->onClick = std::move(callback);
		}

		void setColor(SDL_Color color) {
			this->color = color;
		}
	};
}

#endif