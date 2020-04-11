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
	void podatki(int x, int y, std::string besedilo, SDL_Color barva, SDL_Color bgcolor);
	void drawText(int xpos, int ypos, std::string besedilo, SDL_Color barva);
	void draw();
	void shadedText(int x, int y, std::string besedilo, SDL_Color barva, SDL_Color bgcolor);

private:
	SDL_Texture* m_texture;
	SDL_Rect m_rect;
	int m_size;
	TTF_Font* m_font;
};