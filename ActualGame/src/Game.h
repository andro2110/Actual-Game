#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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
	int lvl = 0;

private:
	int stej = 0;
	bool m_IsRunning;
	SDL_Window* m_window;

	int m_delayHudoba;
	int m_delayStarina;
	int p = 0;
	int m_cas = 300;
	int m_mode;//0 = besedilo stuff, 1 = main game loop, 2 = replay, 3 = konec igre...
};