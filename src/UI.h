#ifndef UI_H
#define UI_H

#include <string>
#include <map>
#include <queue>
#include "SDL_ttf.h"

enum class HorizontalAlignment {
    Left,
    Center,
    Right,
};

enum class VerticalAlignment {
    Top,
    Center,
    Bottom,
};

class UI {

public:
    explicit UI(SDL_Renderer* renderer);
    ~UI();

    void addFont(const std::string& name, const std::string& fontPath, int fontSize);
    void addText(
        const std::string& fontName,
        const std::string& text,
        SDL_Color color,
        int fontSize,
        int x,
        int y,
        HorizontalAlignment horizontalAlignment,
        VerticalAlignment verticalAlignment
    );

    void draw();
    void getWindowSize(int& width, int& height) const;

private:
    struct TextElement {
        SDL_Texture* texture;
        SDL_Rect rect;
    };

    SDL_Renderer *renderer;
    std::map<std::string, std::string> fonts;
    std::queue<TextElement> queue;
};

#endif
