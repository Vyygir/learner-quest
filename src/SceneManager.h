#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <memory>
#include <map>

#include "Game.h"
#include "Interface.h"

class Scene;

struct AdditiveScene {
	bool visible = false;
	std::shared_ptr<Scene> scene;
};

class SceneManager {
public:
	SceneManager(Game *game, Interface *ui) : game(game), ui(ui) {}

	void changeScene(const std::string &sceneName);
	void updateCurrentScene(float delta);
	void tickScene();
	void addScene(const std::string &sceneName, std::shared_ptr<Scene> scene);
	void exitCurrentScene();

	void addAdditiveScene(const std::string &name, const std::shared_ptr<Scene>& scene);
	std::shared_ptr<Scene> getAdditiveScene(const std::string &name);
	void showAdditiveScene(const std::string &name);
	void hideAdditiveScene(const std::string &name);
	void removeAdditiveScene(const std::string &name);

	[[nodiscard]]
	std::shared_ptr<Scene> getCurrentScene() const {
		return currentScene;
	};

private:
	Game *game;
	Interface *ui;

	std::shared_ptr<Scene> currentScene = nullptr;
	std::map<std::string, std::shared_ptr<Scene>> scenes;

	std::map<std::string, AdditiveScene> additivesScenes;
};

#endif
