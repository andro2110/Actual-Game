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

	int m_vrsta;

	SDL_Rect m_srcRect, m_destRect;
};