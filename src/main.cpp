#include <tuple>
#include <string>
#include <random>

#ifdef _WIN32
#include <windows.h>
#endif

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_ttf.h"

#include "Game.h"
#include "Events.h"
#include "UI.h"
#include "SceneManager.h"
#include "Utilities/Logger.h"

// Scenes
#include "Scenes/Main.h"
#include "Scenes/Second.h"
#include "Scenes/Third.h"

const char* TITLE = "2D Adventure Game";

const std::tuple<int, int> RESOLUTION = std::make_tuple(1280, 720);

const int FRAME_RATE     = 144;
const int ENGINE_SPEED   = 60;
const Uint32 FIXED_INTERVAL = 1000 / ENGINE_SPEED;

void clean(SDL_Window* window) {
    SDL_DestroyWindow(window);
}

void clean(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

std::tuple<bool, SDL_Window*, SDL_Renderer*> setup() {
    bool init_failed = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        init_failed = true;
    }

    auto [width, height] = RESOLUTION;
    SDL_Window* window = SDL_CreateWindow(
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

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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

    Game game(window, renderer);
    UI ui(renderer);
    SceneManager sceneManager(&game, &ui);
    Events events(&game, &sceneManager);

    game.setRunning(true);

    ui.addFont("Atkinson", "assets/fonts/AtkinsonHyperlegible-Regular.ttf");
    ui.addFont("Atkinson Bold", "assets/fonts/AtkinsonHyperlegible-Bold.ttf");
    ui.addFont("Atkinson Italic", "assets/fonts/AtkinsonHyperlegible-Italic.ttf");
    ui.addFont("Atkinson Bold Italic", "assets/fonts/AtkinsonHyperlegible-BoldItalic.ttf");

    sceneManager.addScene("Main", std::make_unique<Scenes::Main>());
    sceneManager.addScene("Second", std::make_unique<Scenes::Second>());
    sceneManager.addScene("Third", std::make_unique<Scenes::Third>());

    // Set the default scene.
    sceneManager.changeScene("Main");

    Uint32 frameStart, frameTime, lag = 0;

    unsigned int rgb[3];
    int ticks = 0;

    while (game.isRunning()) {
        frameStart = SDL_GetTicks();

        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsed = currentTime - game.getPreviousTime();

        game.setPreviousTime(currentTime);
        lag += elapsed;

        SDL_Color background = ui.getBackgroundColor();

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);

        while (lag >= FIXED_INTERVAL) {
            events.handle();
            game.update();

            lag -= FIXED_INTERVAL;
            ticks++;
        }

        sceneManager.updateCurrentScene((float) currentTime);
        ui.draw();

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
