#include <utility>
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::changeScene(const std::string &sceneName) {
	this->exitCurrentScene();

	this->currentScene = scenes[sceneName];
	this->additivesScenes.clear();

	if (this->currentScene && !this->currentScene->isLoaded()) {
		this->currentScene->onLoad();
	}
}

void SceneManager::updateCurrentScene(float delta) {
	if (this->currentScene) {
		this->currentScene->onUpdate(delta);
	}

	if (!this->additivesScenes.empty()) {
		for (auto it = this->additivesScenes.begin(); it != this->additivesScenes.end(); it++) {
			AdditiveScene additive = it->second;

			if (!additive.visible) {
				continue;
			}

			additive.scene->onUpdate(delta);
		}
	}
}

void SceneManager::tickScene() {
	if (this->currentScene) {
		this->currentScene->onTick();
	}

	if (!this->additivesScenes.empty()) {
		for (auto it = this->additivesScenes.begin(); it != this->additivesScenes.end(); it++) {
			AdditiveScene additive = it->second;

			if (!additive.visible) {
				continue;
			}

			additive.scene->onTick();
		}
	}
}

void SceneManager::addScene(const std::string &sceneName, std::shared_ptr<Scene> scene) {
	scene->setContext(this->game, this, this->ui);
	scenes[sceneName] = std::move(scene);
}

void SceneManager::exitCurrentScene() {
	if (this->currentScene) {
		this->currentScene->onExit();
		this->additivesScenes.clear();
	}
}

void SceneManager::addAdditiveScene(const std::string &name, const std::shared_ptr<Scene>& scene) {
	if (this->additivesScenes.find(name) != this->additivesScenes.end()) {
		Logger::warn("Additive scene \"" + name + "\" already exists; skipping");
		return;
	}

	this->additivesScenes[name] = AdditiveScene{ false, scene };
}

std::shared_ptr<Scene> SceneManager::getAdditiveScene(const std::string &name) {
	if (this->additivesScenes.find(name) == this->additivesScenes.end()) {
		Logger::log("No additive scene called \"" + name + "\" exists");
		return nullptr;
	}

	return this->additivesScenes[name].scene;
}

std::map<std::string, AdditiveScene> SceneManager::getAdditiveScenes(bool getVisibleOnly) {
	auto additives = this->additivesScenes;

	if (getVisibleOnly) {
		auto it = additives.begin();

		while (it != additives.end()) {
			if (it->second.visible == false) {
				additives.erase(it++);
			} else {
				++it;
			}
		}
	}

	return additives;
}

void SceneManager::showAdditiveScene(const std::string &name) {
	if (this->additivesScenes.find(name) == this->additivesScenes.end()) {
		Logger::log("Unable to show additive scene; no entry called \"" + name + "\" exists");
		return;
	}

	AdditiveScene additive = this->additivesScenes[name];

	if (additive.visible == false) {
		this->additivesScenes[name].visible = true;
	}

	additive.scene->onLoad();
}

void SceneManager::hideAdditiveScene(const std::string &name) {
	if (this->additivesScenes.find(name) == this->additivesScenes.end()) {
		Logger::log("Unable to hide additive scene; no entry called \"" + name + "\" exists");
		return;
	}

	AdditiveScene additive = this->additivesScenes[name];

	if (additive.visible == true) {
		this->additivesScenes[name].visible = false;
	}

	additive.scene->onExit();
}

void SceneManager::removeAdditiveScene(const std::string &name) {
	if (this->additivesScenes.find(name) == this->additivesScenes.end()) {
		Logger::log("Unable to remove additive scene, no entry called \"" + name + "\" exists");
		return;
	}

	this->additivesScenes[name].scene->onExit();
	this->additivesScenes.erase(name);
}

void SceneManager::clearAdditiveScenes() {
	this->additivesScenes.clear();
}
