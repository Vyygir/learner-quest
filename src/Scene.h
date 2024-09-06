#ifndef SCENE_H
#define SCENE_H

#include "Game.h"
#include "Interface.h"
#include "Utilities/Logger.h"

class SceneManager;

class Scene {
public:
	virtual ~Scene() = default;

	void setContext(Game *game, SceneManager *sceneManager, Interface *ui) {
		this->game = game;
		this->sceneManager = sceneManager;
		this->ui = ui;
	}

	virtual void onLoad() {};
	virtual void onUpdate(float delta) {};
	virtual void onTick() {};
	virtual void onMouseMove(SDL_MouseMotionEvent event) {};
	virtual void onMouseButton(SDL_MouseButtonEvent event) {};
	virtual void onExit() {};

	[[nodiscard]]
	bool isLoaded() const { return loaded; }

protected:
	Game *game;
	SceneManager *sceneManager;
	Interface *ui;

	bool loaded = false;

	void addElement(const std::string &name, UI::Element* element) {
		if (this->elements.find(name) != this->elements.end()) {
			Logger::warn("An element called \"" + name + "\" has already been added to this scene");
			return;
		}

		this->elements[name] = element;
	}

	template <typename T>
	T* getElement(const std::string &name) {
		if (this->elements.find(name) == this->elements.end()) {
			Logger::warn("Couldn't find an element called \"" + name + "\" in this scene");
			return nullptr;
		}

		return dynamic_cast<T*>(this->elements[name]);
	}

private:
	std::map<std::string, UI::Element*> elements;
};

#endif