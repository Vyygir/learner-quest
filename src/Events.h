#ifndef EVENTS_H
#define EVENTS_H

#include "Game.h"
#include "Interface.h"
#include "SceneManager.h"

class Events {
public:
	Events(Game *game, Interface *ui, SceneManager *sceneManager);

	void handle();

private:
	Game *game;
	Interface *ui;
	SceneManager *sceneManager;
	SDL_Event event{};

	void keyPress(SDL_Keycode code);
	void handleWindowEvent(SDL_Event e);
};

#endif
