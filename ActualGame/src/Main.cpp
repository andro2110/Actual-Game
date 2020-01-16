#include "Game.h"
#include <iostream>
#include <ctime>
#undef main

int main(int argc, char* argv[])
{
	srand(time(NULL));
	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Game* game = new Game();

	game->Init("Naslov", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_RESIZABLE);

	while (game->IsRunning()) {

		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY > frameTime) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	game->Clean();

	return 0;
}