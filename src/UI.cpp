#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Utilities/Logger.h"
#include "UI.h"

UI::UI(SDL_Renderer* renderer) :
    renderer(renderer)
{
    if (TTF_Init() != 0) {
        Logger::error("Wasn't able to initialise TTF_Font: " + std::string(TTF_GetError()));
    }
}

// This should be the destructor:
UI::~UI() {
    TTF_Quit();
}

void UI::addFont(const std::string& name, const std::string& fontPath, int fontSize) {
    this->fonts[name] = fontPath;
}

void UI::addText(
    const std::string& fontName,
    const std::string& text,
    SDL_Color color,
    int fontSize = 18,
    int x = 0,
    int y = 0,
    HorizontalAlignment horizontalAlign = HorizontalAlignment::Left,
    VerticalAlignment verticalAlign = VerticalAlignment::Top
) {
    int windowWidth, windowHeight;
    this->getWindowSize(windowWidth, windowHeight);

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

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture) {
        Logger::warn("Couldn't create texture from surface:");
        Logger::warn(SDL_GetError());

        SDL_FreeSurface(surface);

        return;
    }

    SDL_Rect rect;

    rect.w = surface->w;
    rect.h = surface->h;

    switch (horizontalAlign) {
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

    switch (verticalAlign) {
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

    rect.x += x;
    rect.y += y;

    SDL_FreeSurface(surface);

    queue.push({ texture, rect });

//    TTF_CloseFont(font);
}

void UI::draw() {
    while (!this->queue.empty()) {
        TextElement element = queue.front();
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
