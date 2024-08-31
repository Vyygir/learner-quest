#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <memory>
#include <chrono>

class Game {
public:
	Game(SDL_Window *window, SDL_Renderer *renderer);

	void setCurrentTime(Uint32 time);
	void setPreviousTime(Uint32 time);
	void setLag(Uint32 lag);
	void setRunning(bool isRunning);
	void setFullscreen(bool isFullscreen);

	SDL_Renderer *getRenderer();
	[[nodiscard]] Uint32 getPreviousTime() const;
	[[nodiscard]] Uint32 getCurrentTime() const;
	[[nodiscard]] Uint32 getLag() const;
	[[nodiscard]] bool isRunning() const;
	[[nodiscard]] bool isFullscreen() const;

	void update();
	void quit();

private:
	bool running;
	bool fullscreen;

	SDL_Window *window;
	SDL_Renderer *renderer;
	Uint32 previousTime;
	Uint32 currentTime;
	Uint32 lag;
};

#endif