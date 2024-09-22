#ifndef SCENE_H
#define SCENE_H

#include "Game.h"
#include "Interface.h"
#include "Utilities/Logger.h"
#include "UI/Elements.h"

class SceneManager;

class Scene {
public:
	 virtual ~Scene() {
		this->elements.clear();
	};

	void setContext(Game *game, SceneManager *sceneManager, Interface *ui) {
		this->game = game;
		this->sceneManager = sceneManager;
		this->ui = ui;
	}

	virtual void onLoad() {};
	virtual void onUpdate(float delta) {
		for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
			auto* element = it->second;

			element->setUnderneathElement(false);

			for (auto jt = elements.rbegin(); jt != elements.rend(); ++jt) {
				if (it != jt) {
					SDL_Rect elementRect = element->getRect();
					SDL_Rect overlapRect = jt->second->getRect();

					if (
						elementRect.x > overlapRect.x &&
						(elementRect.x + elementRect.w) < (overlapRect.x + overlapRect.w) &&
						elementRect.y > overlapRect.y &&
						(elementRect.y + elementRect.h) < (overlapRect.y + overlapRect.h)
					) {
						element->setUnderneathElement(true);
					}
				}
			}
		}
	};

	virtual void onTick() {};
	virtual void onMouseMove(SDL_MouseMotionEvent event) {};
	virtual void onMouseButton(SDL_MouseButtonEvent event) {};
	virtual void onResize(int newWidth, int newHeight) {};
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

		element->setName(name);

		this->elements[name] = element;
	}

	void addElement(const std::string &name, const std::string &parent, UI::Element* element) {
		if (this->elements.find(name) != this->elements.end()) {
			Logger::warn("An element called \"" + name + "\" has already been added to this scene");
			return;
		}

		if (this->elements.find(parent) == this->elements.end()) {
			Logger::warn("Parent element could not be assigned. No element called  \"" + parent + "\" is in this scene");
			return;
		}

		element->setName(name);
		element->setParent(this->elements[parent]);

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