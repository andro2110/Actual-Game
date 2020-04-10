#include "Besedilo.h"

Text::Text(int size)
{
	m_size = size;
	m_font = TTF_OpenFont("Assets/comic.ttf", m_size);//zalaufa text
}

void Text::podatki(int xpos, int ypos, std::string besedilo, SDL_Color txtClr, SDL_Color bgClr)
{
	m_rect.x = xpos;
	m_rect.y = ypos;

	SDL_Surface* surf = TTF_RenderText_Shaded(m_font, besedilo.c_str(), txtClr, bgClr);
	m_texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);//naredi texturo za text

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h);
}

void Text::drawText(int xpos, int ypos, std::string besedilo, SDL_Color barva)
{
	m_rect.x = xpos;
	m_rect.y = ypos;

	SDL_Surface* surf = TTF_RenderText_Blended(m_font, besedilo.c_str(), barva);
	m_texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h);

	SDL_RenderCopy(Game::renderer, m_texture, nullptr, &m_rect);
	SDL_DestroyTexture(m_texture);//unic texturo, da ni memory leaka k se skos dela
}

void Text::draw()
{
	SDL_RenderCopy(Game::renderer, m_texture, nullptr, &m_rect);
	SDL_DestroyTexture(m_texture);
}