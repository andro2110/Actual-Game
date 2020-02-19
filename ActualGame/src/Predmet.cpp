#include "Predmet.h"

Predmet::Predmet(const char* path, float scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 10;
	m_srcRect.h = 30;

	m_position.x = 0;
	m_position.y = 0;

	m_smer.x = 0;
	m_smer.y = 0;

	m_scale = scale;
}

void Predmet::update()
{
	
}

void Predmet::render()
{
	SDL_RenderCopy(Game::renderer, m_texture, &m_srcRect, &m_destRect);
}

void Predmet::posUpdate()
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

void Predmet::premik()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_a:
			m_smer.x = -1;
			break;
		case SDLK_w:
			m_smer.y = -1;
			break;
		case SDLK_s:
			m_smer.y = 1;
			break;
		case SDLK_d:
			m_smer.x = 1;
		default:
			break;
		}
	}

	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_a:
			m_smer.x = 0;
			break;
		case SDLK_w:
			m_smer.y = 0;
			break;
		case SDLK_s:
			m_smer.y = 0;
			break;
		case SDLK_d:
			m_smer.x = 0;
		default:
			break;
		}
	}
}

void Predmet::border()
{
	//za velikost 10x30
	if (m_position.x < -5)
		m_position.x = -6;
	else if (m_position.x >= 785)
		m_position.x = 785;

	if (m_position.y < -50)
		m_position.y = -50;
	else if (m_position.y > 610)
		m_position.y = 610;
	//za velikost 10x30
}

bool Predmet::checkCollision(SDL_Rect dest, SDL_Rect src)
{
	/*if (m_position.x <= (dest.x + src.w) && m_position.y >= (dest.y + src.h))//levo zgori
	{
		return true;
		std::cout << "Prva" << std::endl;
	}

	if ((m_position.x + m_srcRect.w) >= dest.x && m_position.y <= (dest.y + src.h))//desno zgori
	{
		return true;
		std::cout << "Druga" << std::endl;
	}

	if (m_position.x <= (dest.x + src.w) && (m_position.y + m_srcRect.h) >= dest.y)//levo spodi
	{
		return true;
		std::cout << "Tretja" << std::endl;
	}

	if ((m_position.x + m_srcRect.w) >= dest.x && (m_position.y + m_srcRect.h) >= dest.y) //desno spodi
	{
		return true;
		std::cout << "Cetrta" << std::endl;
	}

	return false;*/

	if ((m_position.x + m_srcRect.w) >= dest.x && m_position.x <= dest.x + src.w && m_position.y + m_srcRect.h >= dest.y && m_position.y <= dest.y + src.h)
		return true;
	else
		return false;
}

Igralec::Igralec(const char* path, float scale) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 10;
	m_srcRect.h = 30;

	m_position.x = 0;
	m_position.y = 0;

	m_scale = scale;
}

void Igralec::update()
{
	Predmet::premik();
	Predmet::border();

	posUpdate();
}

void Igralec::posUpdate()
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_position.x += m_smer.x * m_speed;
	m_position.y += m_smer.y * m_speed;

	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	//std::cout << m_position.x << ", " << m_position.y << std::endl;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

Hudoba::Hudoba(const char* path, float scale) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 10;
	m_srcRect.h = 30;

	m_position.x = rand() % 758 + 3;
	m_position.y = rand() % 520 + 3;

	m_randx = rand() % 758 + 3;
	m_randy = rand() % 520 + 3;

	m_scale = scale;
}

void Hudoba::update()
{
	Predmet::border();
	posUpdate();
	preveriPos();
	premakni();
}

void Hudoba::posUpdate()
{
	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

void Hudoba::premakni()
{
	if (m_position.x > m_randx)
		m_position.x--;
	else if (m_position.x < m_randx)
		m_position.x++;

	if (m_position.y > m_randy)
		m_position.y--;
	else if (m_position.y < m_randy)
		m_position.y++;
}

void Hudoba::preveriPos()
{
	if (m_position.x == m_randx && m_position.y == m_randy)
	{
		m_pravoMesto = 1;
		m_framecount++;
		if (m_framecount == 100)
		{
			m_randx = rand() % 758 + 3;
			m_randy = rand() % 520 + 3;

			m_framecount = 0;
		}
	}
	else
		m_pravoMesto = 0;
}

void Hudoba::changePos(int x, int y)
{
	if (m_position.x > x)
		m_position.x--;
	else if (m_position.x < x)
		m_position.x++;

	if (m_position.y > y)
		m_position.y--;
	else if (m_position.y < y)
		m_position.y++;
}

Staroselec::Staroselec(const char* path, float scale) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 10;
	m_srcRect.h = 25;

	m_position.x = rand() % 750 + 5;
	m_position.y = rand() % 520 + 5;

	m_nasMestox = rand() % 750 + 5;
	m_nasMestoy = rand() % 520 + 5;

	m_scale = scale;
}

void Staroselec::update()
{
	Predmet::border();
	posUpdate();
	premakni();
	preveriPos();
}

void Staroselec::posUpdate()
{
	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

void Staroselec::premakni()
{
	if (m_position.x > m_nasMestox)
		m_position.x -= 0.5;
	else if (m_position.x < m_nasMestox)
		m_position.x += 0.5;

	if (m_position.y < m_nasMestoy)
		m_position.y += 0.5;
	else if (m_position.y > m_nasMestoy)
		m_position.y -= 0.5;
}

void Staroselec::getHudoba(int x, int y)
{
	m_hux = x;
	m_huy = y;
}

void Staroselec::changePos(int x, int y)//og se prenese iz map.cpp, ko zazna ogenj 3 indexe desno
{
	m_nasMestox = x;
	m_nasMestoy = y;
	m_zasedenost = 1;
}

void Staroselec::preveriPos()
{
	if (m_zasedenost == 1)//ogenj je v vidnem polju
	{
		if (m_position.x == m_nasMestox && m_position.y == m_nasMestoy)//pride do tapravega mesta
		{
			m_pravoMesto = 1;
			m_zasedenost = 0;
			m_framecount++;
			if (m_framecount == 100)
			{
				m_nasMestox = rand() % 750 + 5;
				m_nasMestoy = rand() % 520 + 5;//mesto gre spet na random, ko pride do pozara

				m_framecount = 0;
			}
		}
		else
			m_pravoMesto = 0;
	}
	else
	{
		if (m_position.x == m_nasMestox && m_position.y == m_nasMestoy)
		{
			m_pravoMesto = 1;
			m_framecount++;
			m_zasedenost = 0;
			if (m_framecount == 100)
			{
				m_nasMestox = rand() % 750 + 5;
				m_nasMestoy = rand() % 520 + 5;//mesto gre spet na random

				m_framecount = 0;
			}
		}
		else
			m_pravoMesto = 0;
	}
}

Predmet::~Predmet() {}
Igralec::~Igralec() {}
Hudoba::~Hudoba() {}
Staroselec::~Staroselec() {}