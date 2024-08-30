#ifndef UI_H
#define UI_H

#include <string>
#include <map>
#include <queue>
#include "SDL_ttf.h"

struct Offset {
    int x;
    int y;
};

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

struct Alignment {
    HorizontalAlignment x;
    VerticalAlignment y;
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
        Offset offset,
        Alignment alignment
    );

    void draw();

private:
    struct UIElement {
        SDL_Texture* texture;
        SDL_Rect rect;
    };

    SDL_Renderer *renderer;
    std::map<std::string, std::string> fonts;
    std::queue<UIElement> queue;

    void createElement(SDL_Surface* surface, Offset offset, Alignment alignment);
    void getWindowSize(int& width, int& height) const;
};

#endif
