#include <string>
#include "SDL.h"
#include "Events.h"
#include "Utilities/Logger.h"
#include "Scene.h"

Events::Events(Game *game, SceneManager *sceneManager) : game(game), sceneManager(sceneManager) {}

void Events::handle() {
	while (SDL_PollEvent(&event) != 0) {
		Uint32 type = event.type;

		if (type == SDL_QUIT) {
			this->game->quit();
		}

		if (type == SDL_WINDOWEVENT_RESIZED) {
			this->handleWindowEvent(event);
		}

		if (type == SDL_KEYDOWN) {
			this->keyPress(event.key.keysym.sym);
		}

		// Handling scene events.
		std::shared_ptr<Scene> currentScene = this->sceneManager->getCurrentScene();

		if (currentScene) {
			if (type == SDL_MOUSEMOTION) {
				currentScene->onMouseMove(event.motion);
			}

			if (type == SDL_MOUSEBUTTONDOWN) {
				currentScene->onMouseButton(event.button);
			}
		}
	}
}

void Events::keyPress(SDL_Keycode code) {
	switch (code) {
		case SDL_KeyCode::SDLK_F11:
			this->game->setFullscreen(!this->game->isFullscreen());
			break;

		case SDL_KeyCode::SDLK_q:
			this->game->quit();
			break;

		case SDL_KeyCode::SDLK_1:
			this->sceneManager->changeScene("Main");
			break;

		case SDL_KeyCode::SDLK_2:
			this->sceneManager->changeScene("Second");
			break;

		case SDL_KeyCode::SDLK_3:
			this->sceneManager->changeScene("Third");
			break;
	}
}

void Events::handleWindowEvent(SDL_Event e) {
	Logger::log(std::to_string(e.window.event));
}
