#pragma once

#include <SDL.h>
#include "SDL_image.h"

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int x, int y, int w, int h, Uint32 flags);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	int getFrame() { return m_Framecount; }

	bool IsRunning() { return m_IsRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	int m_Framecount;
	static bool homesc;

private:
	bool m_IsRunning;
	SDL_Window* m_window;
};