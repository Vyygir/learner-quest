#include <utility>
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::changeScene(const std::string &sceneName) {
	if (this->currentScene) {
		this->currentScene->onExit();
	}

	this->currentScene = scenes[sceneName];

	if (this->currentScene && !this->currentScene->isLoaded()) {
		this->currentScene->onLoad();
	}
}

void SceneManager::updateCurrentScene(float delta) {
	if (this->currentScene) {
		this->currentScene->onUpdate(delta);
	}
}

void SceneManager::tickScene() {
	if (this->currentScene) {
		this->currentScene->onTick();
	}
}

void SceneManager::addScene(const std::string &sceneName, std::shared_ptr<Scene> scene) {
	scene->setContext(this->game, this, this->ui);
	scenes[sceneName] = std::move(scene);
}

void SceneManager::exitCurrentScene() {
	if (this->currentScene) {
		this->currentScene->onExit();
	}
}
