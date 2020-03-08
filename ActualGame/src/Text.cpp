/*#include <string>
#include "Text.h"

void Text::getFont(std::string path, int size)
{
	TTF_OpenFont(path.c_str(), size);
}

void Text::setText(std::string text, std::string font)
{
	SDL_Surface* surf = TTF_RenderText_Blended(m_font, m_text.c_str(), m_barva);
	m_textTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);

	SDL_QueryTexture(m_textTexture, nullptr, nullptr, &m_position.w, &m_position.h);
}*/