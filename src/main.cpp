#include <tuple>
#include <string>
#include <random>

#ifdef _WIN32

#include <windows.h>

#endif

#define SDL_MAIN_HANDLED

#include "SDL.h"
#include "SDL_ttf.h"

#include "Options.h"
#include "Game.h"
#include "Events.h"
#include "Interface.h"
#include "SceneManager.h"
#include "Utilities/Logger.h"

// Scenes
#include "Scenes/MainMenu.h"
#include "Scenes/Credits.h"

void clean(SDL_Window *window) {
	SDL_DestroyWindow(window);
}

void clean(SDL_Window *window, SDL_Renderer *renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

std::tuple<bool, SDL_Window *, SDL_Renderer *> setup() {
	bool init_failed = false;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		init_failed = true;
	}

	auto [width, height] = RESOLUTION;
	SDL_Window *window = SDL_CreateWindow(
			TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	if (!window) {
		init_failed = true;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		clean(window);
		init_failed = true;
	}

	return std::make_tuple(init_failed, window, renderer);
}


int main() {
	auto [init_failed, window, renderer] = setup();

	if (init_failed) {
		Logger::error("Failed to initialise SDL:\n\t" + std::string(SDL_GetError()));
		return 1;
	}

	Interface::initialise(renderer);

	Game game(window, renderer);
	Interface& ui = Interface::getInstance();
	SceneManager sceneManager(&game, &ui);
	Events events(&game, &ui, &sceneManager);

	game.setRunning(true);

	ui.addFont("Atkinson", "assets/fonts/AtkinsonHyperlegible-Regular.ttf");
	ui.addFont("Atkinson Bold", "assets/fonts/AtkinsonHyperlegible-Bold.ttf");
	ui.addFont("Atkinson Italic", "assets/fonts/AtkinsonHyperlegible-Italic.ttf");
	ui.addFont("Atkinson Bold Italic", "assets/fonts/AtkinsonHyperlegible-BoldItalic.ttf");
	ui.addFont("Mini Pixel", "assets/fonts/MiniPixel-7.ttf");

	sceneManager.addScene("MainMenu", std::make_unique<Scenes::MainMenu>());
	sceneManager.addScene("Credits", std::make_unique<Scenes::Credits>());

	// Set the default scene.
	sceneManager.changeScene("MainMenu");

	Uint32 frameStart, frameTime, lag = 0;
	int ticks = 0;

	while (game.isRunning()) {
		frameStart = SDL_GetTicks();

		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsed = currentTime - game.getPreviousTime();

		game.setPreviousTime(currentTime);
		lag += elapsed;

		SDL_RenderClear(renderer);

		while (lag >= FIXED_INTERVAL) {
			game.update();

			lag -= FIXED_INTERVAL;
			ticks++;

			if (ticks >= 3) {
				sceneManager.tickScene();
				ticks = 0;
			}
		}

		sceneManager.updateCurrentScene((float) currentTime);
		events.handle();

		SDL_Color background = ui.getBackgroundColor();

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < (1000 / FRAME_RATE)) {
			SDL_Delay((1000 / FRAME_RATE) - frameTime);
		}
	}

	clean(window, renderer);

	TTF_Quit();
	SDL_Quit();

	return 0;
}

//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//    run();
//    return 0;
//}
