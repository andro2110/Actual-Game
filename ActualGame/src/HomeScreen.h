#pragma once
#include "TextureManager.h"

class Homesc
{
public:
	Homesc();
	~Homesc();

	void getVrsta(int v) { m_vrsta = v; }
	void draw();
	void pojdiNazaj();

private:
	SDL_Texture* m_homeScreen;
	SDL_Texture* m_credits;
	SDL_Texture* m_howToPlay;

	int m_vrsta;

	SDL_Rect m_srcRect, m_destRect;
};