#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Utilities/Logger.h"
#include "UI.h"

UI::UI(SDL_Renderer* renderer) :
    renderer(renderer)
{
    if (TTF_Init() != 0) {
        Logger::error("Wasn't able to initialise TTF_Font: " + std::string(TTF_GetError()));
    }

    if (IMG_Init(IMG_INIT_PNG) != 0) {
        Logger::error("Wasn't able to initialise SDL2_image: " + std::string(IMG_GetError()));
    }
}

UI::~UI() {
    TTF_Quit();
    IMG_Quit();
}

void UI::addFont(const std::string& name, const std::string& fontPath) {
    this->fonts[name] = fontPath;
}

void UI::addImage(const std::string& path, Dimensions dimensions, Alignment alignment, Offset offset) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface) {
        Logger::warn("Couldn't load image at \"" + path + "\":\n\t" + IMG_GetError());
        return;
    }

    createElement(surface, dimensions, { 1.0f, 1.0f }, offset, alignment);
}

void UI::addImage(const std::string& path, Scale scale, Alignment alignment, Offset offset) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface) {
        Logger::warn("Couldn't load image at \"" + path + "\":\n\t" + IMG_GetError());
        return;
    }

    createElement(surface, { -1, -1 }, scale, offset, alignment);
}

void UI::addText(
    const std::string& fontName,
    const std::string& text,
    SDL_Color color,
    int fontSize,
    Alignment alignment,
    Offset offset
) {
    if (this->fonts.find(fontName) == this->fonts.end()) {
        Logger::warn("\"" + std::string(fontName) + "\" isn't a valid font");
        return;
    }

    TTF_Font* font = TTF_OpenFont(this->fonts[fontName].c_str(), fontSize);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (!surface) {
        Logger::warn("Couldn't create surface for text: " + text);
        Logger::log(SDL_GetError());
        return;
    }

    createElement(surface, { -1, -1 }, { 1.0f, 1.0f }, offset, alignment);
}

void UI::createElement(SDL_Surface* surface, Dimensions dimensions, Scale scale, Offset offset, Alignment alignment) {
    int windowWidth, windowHeight;
    this->getWindowSize(windowWidth, windowHeight);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);

    if (!texture) {
        Logger::warn("Couldn't create texture from surface:");
        Logger::warn(SDL_GetError());

        SDL_FreeSurface(surface);

        return;
    }

    if (dimensions.w == -1) {
        dimensions.w = surface->w;
    }

    if (dimensions.h == -1) {
        dimensions.h = surface->h;
    }

    SDL_Rect rect;

    rect.w = dimensions.w;
    rect.h = dimensions.h;

    if (scale.x != 1.0f) {
        rect.w *= scale.x;
    }

    if (scale.y != 1.0f) {
        rect.h *= scale.y;
    }

    switch (alignment.x) {
        case HorizontalAlignment::Left:
            rect.x = 0;
            break;

        case HorizontalAlignment::Center:
            rect.x = (windowWidth - rect.w) / 2;
            break;

        case HorizontalAlignment::Right:
            rect.x = windowWidth - rect.w;
            break;
    }

    switch (alignment.y) {
        case VerticalAlignment::Top:
            rect.y = 0;
            break;

        case VerticalAlignment::Center:
            rect.y = (windowHeight - rect.h) / 2;
            break;

        case VerticalAlignment::Bottom:
            rect.y = windowHeight - rect.h;
            break;
    }

    rect.x += offset.x;
    rect.y += offset.y;

    SDL_FreeSurface(surface);

    queue.push({ texture, rect });
}

void UI::draw() {
    while (!this->queue.empty()) {
        UIElement element = queue.front();
        queue.pop();

        SDL_RenderCopy(this->renderer, element.texture, nullptr, &element.rect);
        SDL_DestroyTexture(element.texture);
    }
}

void UI::getWindowSize(int &width, int &height) const {
    SDL_Window* window = SDL_RenderGetWindow(this->renderer);

    if (!window) {
        Logger::error("Couldn't get window from renderer.");
        return;
    }

    SDL_GetWindowSize(window, &width, &height);
}
