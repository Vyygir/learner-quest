#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "../../Utilities/Logger.h"
#include "../Element.h"

namespace UI {
	class Image : public Element {
	public:
		Image(
			const std::string &imagePath,
			Scale scale,
			Alignment alignment,
			bool scaleToWindow,
			Offset offset
		) : Element(nullptr, {0, 0, 0, 0}, alignment, scale, offset, scaleToWindow) {
			SDL_Surface *surface = IMG_Load(imagePath.c_str());

			if (!surface) {
				Logger::warn("Failed to load image: " + imagePath);
				return;
			}

			this->texture = SDL_CreateTextureFromSurface(Interface::getInstance().getRenderer(), surface);

			this->rect.w = surface->w;
			this->rect.h = surface->h;

			SDL_FreeSurface(surface);
		}
	};
}


#endif
