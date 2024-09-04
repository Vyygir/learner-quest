#ifndef UI_REPEATABLE_IMAGE_H
#define UI_REPEATABLE_IMAGE_H

#include <string>
#include <algorithm>
#include "SDL.h"
#include "SDL_image.h"
#include "../../Utilities/Logger.h"
#include "../Element.h"
#include "Image.h"

namespace UI {
	class RepeatableImage : public Image {
	private:
		bool repeatX;
		bool repeatY;

	public:
		RepeatableImage(
			const std::string &imagePath,
			bool repeatX,
			bool repeatY,
			Scale scale,
			Alignment alignment = { HorizontalAlignment::Left, VerticalAlignment::Top },
			Offset offset = { 0, 0 },
			bool scaleToWindow = false
		) : Image(imagePath, scale, alignment, scaleToWindow, offset), repeatX(repeatX), repeatY(repeatY) {}

		void render() override {
			if (!this->texture) {
				return;
			}

			SDL_Renderer* renderer = Interface::getInstance().getRenderer();

			int windowWidth, windowHeight;
			SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

			updateRectSize(windowWidth, windowHeight, { this->rect.w, this->rect.h });

			int startX = this->rect.x;
			int startY = this->rect.y;

			// Safeguard against division by zero
			int rectWidth = this->rect.w > 0 ? this->rect.w : 1;
			int rectHeight = this->rect.h > 0 ? this->rect.h : 1;

			int endX = this->repeatX
			   ? (startX + ((windowWidth - startX + rectWidth - 1) / rectWidth) * rectWidth)
			   : (startX + rectWidth);
			int endY = this->repeatY
			   ? (startY + ((windowHeight - startY + rectHeight - 1) / rectHeight) * rectHeight)
			   : (startY + rectHeight);

			endX = (std::min)(endX, windowWidth);
			endY = (std::min)(endY, windowHeight);

			for (int y = startY; y < endY; y += rectHeight) {
				for (int x = startX; x < endX; x += rectWidth) {
					SDL_Rect dstRect = { x, y, rectWidth, rectHeight };
					SDL_RenderCopy(renderer, this->texture, nullptr, &dstRect);
				}
			}
		}
	};
}

#endif
