#ifndef SCENE_H
#define SCENE_H

#include "Game.h"
#include "UI.h"

class SceneManager;

class Scene {
public:
	virtual ~Scene() = default;

	void setContext(Game *game, SceneManager *sceneManager, UI *ui) {
		this->game = game;
		this->sceneManager = sceneManager;
		this->ui = ui;
	}

	virtual void onLoad() {};
	virtual void onUpdate(float delta) {};
	virtual void onMouseMove(SDL_MouseMotionEvent event) {};
	virtual void onMouseButton(SDL_MouseButtonEvent event) {};
	virtual void onExit() {};

	[[nodiscard]]
	bool isLoaded() const { return loaded; }

protected:
	Game *game;
	SceneManager *sceneManager;
	UI *ui;

	bool loaded = false;
};

#endif