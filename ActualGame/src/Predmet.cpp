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
	//za obj velikost 16x32
	/*if (m_position.x >= 757)
		m_position.x = 757;
	else if (m_position.x <= -5)
		m_position.x = -5;

	if (m_position.y <= -1)
		m_position.y = -1;
	else if (m_position.y >= 543)
		m_position.y = 543;
	//za obj velikost 16x32*/

	//za velikost 10x30
	if (m_position.x <= 3)
		m_position.x = 3;
	else if (m_position.x >= 768)
		m_position.x = 768;

	if (m_position.y <= 3)
		m_position.y = 3;
	else if (m_position.y >= 550)
		m_position.y = 550;
	//za velikost 10x30
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
	changePos();

	std::cout << "hudoba: " << m_position.x << ", " << m_position.y << std::endl;
}

void Hudoba::posUpdate()
{
	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

void Hudoba::changePos()
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

Staroselec::Staroselec(const char* path, float scale) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 10;
	m_srcRect.h = 25;

	m_position.x = rand() % 758 + 3;
	m_position.y = rand() % 520 + 3;

	m_scale = scale;
}

void Staroselec::update()
{
	Predmet::border();
	posUpdate();
}

void Staroselec::posUpdate()
{
	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

void Staroselec::changePos(int hudx, int hudy)
{
	if (m_position.x > hudy)
		m_position.x -= 0.5;
	else if (m_position.x < hudx)
		m_position.x += 0.5;

	if (m_position.y > hudx)
		m_position.y -= 0.5;
	else if (m_position.y < hudy)
		m_position.y += 0.5;
}

Predmet::~Predmet() {}
Igralec::~Igralec() {}
Hudoba::~Hudoba() {}
Staroselec::~Staroselec() {}