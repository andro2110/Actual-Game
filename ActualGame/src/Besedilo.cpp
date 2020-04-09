#include "Besedilo.h"

Text::Text(int size)
{
	m_size = size;
	m_font = TTF_OpenFont("Assets/comic.ttf", m_size);
}

void Text::podatki(int xpos, int ypos, std::string besedilo, SDL_Color barva)
{
	m_rect.x = xpos;
	m_rect.y = ypos;

	SDL_Surface* surf = TTF_RenderText_Blended(m_font, besedilo.c_str(), barva);
	m_texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h);
}

void Text::drawText()
{
	SDL_RenderCopy(Game::renderer, m_texture, nullptr, &m_rect);
}