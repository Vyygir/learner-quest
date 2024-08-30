#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <memory>
#include <chrono>

class Game {
public:
    Game(SDL_Window* window, SDL_Renderer* renderer);

    void update();

    void setPreviousTime(Uint32 time);
    [[nodiscard]] Uint32 getPreviousTime() const;

    void setCurrentTime(Uint32 time);
    [[nodiscard]] Uint32 getCurrentTime() const;

    void setLag(Uint32 lag);
    [[nodiscard]] Uint32 getLag() const;

    SDL_Renderer* getRenderer();

    void setFullscreen(bool isFullscreen);
    [[nodiscard]] bool isFullscreen() const;

//    void initialiseUILayer(TTF_Font* font, SDL_Renderer* renderer);

    void quit();

    void setRunning(bool isRunning);
    [[nodiscard]] bool isRunning() const;

private:
    bool running;
    bool fullscreen;

    SDL_Window* window;
    SDL_Renderer* renderer;
    Uint32 previousTime;
    Uint32 currentTime;
    Uint32 lag;
};

#endif