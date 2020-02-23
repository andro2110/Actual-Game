#pragma once
#include "TextureManager.h"

class Homesc
{
public:
	Homesc();
	~Homesc();

	void getVrsta(int v) { m_vrsta = v; }
	void preveri();
	void draw();
	

private:
	SDL_Texture* m_homeScreen;
	SDL_Texture* m_credits;
	SDL_Texture* m_howToPlay;
	SDL_Texture* m_gameOver;
	SDL_Texture* m_lvl1;
	SDL_Texture* m_lvl2;
	SDL_Texture* m_lvl3;
	SDL_Texture* m_congrats;

	int m_vrsta;
	int m_framecnt = 0;

	SDL_Rect m_srcRect, m_destRect;
};