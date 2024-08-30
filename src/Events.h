#ifndef EVENTS_H
#define EVENTS_H

#include "Game.h"
#include "SceneManager.h"

class Events {
public:
    Events(Game* game, SceneManager* sceneManager);
    void handle();

private:
    Game* game;
    SceneManager* sceneManager;
    SDL_Event event{};

    void keyPress(SDL_Keycode code);
    void handleWindowEvent(SDL_Event e);
};

#endif
