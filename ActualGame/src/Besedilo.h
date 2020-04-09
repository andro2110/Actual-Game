#pragma once

#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include "Game.h"

class Text
{
public:
	Text() {}
	Text(int size);
	void podatki(int xpos, int ypos, std::string besedilo, SDL_Color barva);
	void drawText();

private:
	SDL_Texture* m_texture;
	SDL_Rect m_rect;
	int m_size;
	TTF_Font* m_font;
};