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
		Scale scale = { 1.0f, 1.0f };
		Dimensions dimensions = { 0, 0 };
		Offset offset;
		Offset normalOffset;
		bool scaleToWindow;
		Dimensions previousWindowSize = { DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT };

		void updateRectSize(int windowWidth, int windowHeight, Dimensions dimensions) {
			if ( this->dimensions.w > 0 && this->dimensions.h > 0) {
				this->rect.w = this->dimensions.w;
				this->rect.h = this->dimensions.h;
			} else if (this->scaleToWindow) {
				bool unscaled = (dimensions.w <= 0 && dimensions.h <= 0);
				float aspectRatio = static_cast<float>(dimensions.w) / static_cast<float>(dimensions.h);

				if (this->scale.x <= 0.0f) {
					this->scale.x = this->scale.y * aspectRatio;
				}

				if (this->scale.y <= 0.0f) {
					this->scale.y = this->scale.x / aspectRatio;
				}

				if (unscaled) {
					this->rect.w = static_cast<int>(windowWidth * this->scale.x);
					this->rect.h = static_cast<int>(windowHeight * this->scale.y);
				} else if (dimensions.w > dimensions.h) {
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
		) : texture(texture), rect(rect), alignment(alignment), scale(scale), offset(offset), normalOffset(offset), scaleToWindow(scaleToWindow), isVisible(true) {}

		Element(
			SDL_Texture *texture,
			SDL_Rect rect,
			Alignment alignment,
			Dimensions dimensions,
			Offset offset,
			bool scaleToWindow
		) : texture(texture), rect(rect), alignment(alignment), dimensions(dimensions), offset(offset), normalOffset(offset), scaleToWindow(scaleToWindow), isVisible(true) {}

		virtual ~Element() {
			if (this->texture) {
				SDL_DestroyTexture(this->texture);
			}
		}

		virtual void preRender(SDL_Renderer* renderer) {
			int windowWidth, windowHeight;
			SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

			if (this->previousWindowSize.w != windowWidth || this->previousWindowSize.h != windowHeight) {
				this->previousWindowSize = { windowWidth, windowHeight };

				this->setOffset(
					{
						(this->normalOffset.x * windowWidth) / DEFAULT_WINDOW_WIDTH,
						(this->normalOffset.y * windowHeight / DEFAULT_WINDOW_HEIGHT)
					}
				);
			}

			updateRectSize(windowWidth, windowHeight, { this->rect.w, this->rect.h });
		}

		virtual void render() {
			if (!this->isVisible || !this->texture) {
				return;
			}

			SDL_Renderer* renderer = Interface::getInstance().getRenderer();

			this->preRender(renderer);

			SDL_RenderCopy(renderer, this->texture, nullptr, &this->rect);
		}

		SDL_Rect getRect() {
			return this->rect;
		}

		void setAlignment(Alignment newAlignment) {
			this->alignment = newAlignment;
		}

		void setScale(Scale newScale) {
			this->scale = newScale;
		}

		void setOffset(Offset newOffset) {
			this->offset = newOffset;
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