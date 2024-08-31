#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <memory>
#include <map>

#include "Game.h"
#include "UI.h"

class Scene;

class SceneManager {
public:
	SceneManager(Game *game, UI *ui) : game(game), ui(ui) {}

	void changeScene(const std::string &sceneName);
	void updateCurrentScene(float delta);
	void addScene(const std::string &sceneName, std::shared_ptr<Scene> scene);
	void exitCurrentScene();

	[[nodiscard]]
	std::shared_ptr<Scene> getCurrentScene() const {
		return currentScene;
	};

private:
	Game *game;
	UI *ui;
	std::shared_ptr<Scene> currentScene = nullptr;
	std::map<std::string, std::shared_ptr<Scene>> scenes;
};

#endif
