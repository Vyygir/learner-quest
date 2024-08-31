#ifndef UI_H
#define UI_H

#include <string>
#include <map>
#include <queue>
#include "SDL_ttf.h"

struct Dimensions {
    int w = -1;
    int h = -1;
};

struct Scale {
    float x = 1.0f;
    float y = 1.0f;
};

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

    void setBackgroundColor(SDL_Color color);
    SDL_Color getBackgroundColor();

    void addFont(const std::string& name, const std::string& fontPath);
    void addImage(
        const std::string& path,
        Dimensions dimensions = { -1, -1 },
        Alignment alignment = { HorizontalAlignment::Left, VerticalAlignment::Top },
        bool repeatX = false,
        bool repeatY = false,
        Offset offset = { 0, 0 }
    );

    void addImage(
        const std::string& path,
        Scale scale = { 1.0f, 1.0f },
        Alignment alignment = { HorizontalAlignment::Left, VerticalAlignment::Top },
        bool repeatX = false,
        bool repeatY = false,
        Offset offset = { 0, 0 }
    );

    void addImage(
        const std::string& path,
        Scale scale = { 1.0f, 1.0f },
        bool scaleToWindow = false,
        Alignment alignment = { HorizontalAlignment::Left, VerticalAlignment::Top },
        bool repeatX = false,
        bool repeatY = false,
        Offset offset = { 0, 0 }
    );

    void addText(
        const std::string& fontName,
        const std::string& text,
        SDL_Color color,
        int fontSize,
        Alignment alignment = { HorizontalAlignment::Left, VerticalAlignment::Top },
        Offset offset = { 0, 0 }
    );

    void draw();

private:
    struct UIElement {
        SDL_Texture* texture;
        SDL_Rect rect;
        Offset offset;
        bool repeatX;
        bool repeatY;
    };

    SDL_Renderer *renderer;
    std::map<std::string, std::string> fonts;
    std::queue<UIElement> queue;
    SDL_Color backgroundColor = { 0, 0, 0, 255 };

    void createElement(
        SDL_Surface* surface,
        Dimensions dimensions,
        Scale scale,
        Offset offset,
        Alignment alignment,
        bool repeatX = false,
        bool repeatY = false,
        bool scaleToWindow = false
    );

    void getWindowSize(int& width, int& height) const;
};

#endif
