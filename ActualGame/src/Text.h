/*#include <string>
#include "Game.h"
#include "SDL_ttf.h"


class Text
{
public:
	void pripraviText(int xpos, int ypos, std::string text, SDL_Color& colour)
	{
		m_text = text;
		m_barva = colour;

		m_position.x = xpos;
		m_position.y = ypos;

		setText(text, font);
	}

	void getFont(std::string path, int size);
	void setText(std::string text, std::string font);

	void draw()
	{
		SDL_RenderCopy(Game::renderer, m_textTexture, nullptr, &m_position);
	}

private:
	SDL_Rect m_position;
	std::string m_text;
	std::string font;
	SDL_Color m_barva;
	SDL_Texture* m_textTexture;
	TTF_Font* m_font;
};*/