#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#pragma once

#include "SDL.h"
#include "Forward/Element.h"

namespace UI {
	class Element {
	protected:
		SDL_Texture *texture;
		SDL_Rect rect;
		bool isVisible;
		Alignment alignment;
		Scale scale;
		Offset offset;
		bool scaleToWindow;

		void updateRectSize(int windowWidth, int windowHeight, Dimensions dimensions) {
			// Scale the dimensions based on the provided scale and window size.
			if (this->scaleToWindow) {
				float aspectRatio = static_cast<float>(dimensions.w) / static_cast<float>(dimensions.h);

				if (this->scale.x <= 0.0f) {
					this->scale.x = this->scale.y * aspectRatio;
				}

				if (this->scale.y <= 0.0f) {
					this->scale.y = this->scale.x / aspectRatio;
				}

				if (dimensions.w > dimensions.h) {
					this->rect.w = static_cast<int>(windowWidth * this->scale.x);
					this->rect.h = static_cast<int>(this->rect.w / aspectRatio);

					if (this->rect.h > windowHeight * this->scale.y) {
						this->rect.h = static_cast<int>(windowHeight * this->scale.y);
						this->rect.w = static_cast<int>(this->rect.h * aspectRatio);
					}
				} else {
					this->rect.h = static_cast<int>(windowHeight * this->scale.y);
					this->rect.w = static_cast<int>(this->rect.h * aspectRatio);

					if (this->rect.w > windowWidth * this->scale.x) {
						this->rect.w = static_cast<int>(windowWidth * this->scale.x);
						this->rect.h = static_cast<int>(this->rect.w / aspectRatio);
					}
				}
			} else {
				if (this->scale.x != 1.0f) {
					this->rect.w *= this->scale.x;
				}

				if (this->scale.y != 1.0f) {
					this->rect.h *= scale.y;
				}
			}

			// Horizontal alignment
			switch (alignment.x) {
				case HorizontalAlignment::Left:
					this->rect.x = 0;
					break;
				case HorizontalAlignment::Center:
					this->rect.x = (windowWidth - this->rect.w) / 2;
					break;
				case HorizontalAlignment::Right:
					this->rect.x = windowWidth - this->rect.w;
					break;
			}

			// Vertical alignment
			switch (alignment.y) {
				case VerticalAlignment::Top:
					this->rect.y = 0;
					break;
				case VerticalAlignment::Center:
					this->rect.y = (windowHeight - this->rect.h) / 2;
					break;
				case VerticalAlignment::Bottom:
					this->rect.y = windowHeight - this->rect.h;
					break;
			}

			// Apply the offset
			this->rect.x += offset.x;
			this->rect.y += offset.y;
		}

	protected:
		[[nodiscard]]
		bool isWithinBounds(int x, int y) const {
			if (x < this->rect.x || x > (this->rect.x + this->rect.w)) {
				return false;
			}

			if (y < this->rect.y || y > (this->rect.y + this->rect.h)) {
				return false;
			}

			return true;
		}

	public:
		Element(
			SDL_Texture *texture,
			SDL_Rect rect,
			Alignment alignment,
			Scale scale,
			Offset offset,
			bool scaleToWindow
		) : texture(texture), rect(rect), alignment(alignment), scale(scale), offset(offset), scaleToWindow(scaleToWindow), isVisible(true) {}

		virtual ~Element() {
			if (this->texture) {
				SDL_DestroyTexture(this->texture);
			}
		}

		virtual void render() {
			if (!this->isVisible || !this->texture) {
				return;
			}

			SDL_Renderer* renderer = Interface::getInstance().getRenderer();

			int windowWidth, windowHeight;
			SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

			updateRectSize(windowWidth, windowHeight, { rect.w, rect.h });
			SDL_RenderCopy(renderer, this->texture, nullptr, &this->rect);
		}

		void setVisibility(bool visibility) {
			this->isVisible = visibility;
		}

		bool getVisibility() const {
			return this->isVisible;
		}

		virtual void handleEvent(const SDL_Event &event) {};
	};
}

#endif