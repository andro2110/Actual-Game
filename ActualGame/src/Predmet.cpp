#include "Predmet.h"

Predmet::Predmet(const char* path, float scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 16;
	m_srcRect.h = 32;

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
	/*//za obj velikost 32
	if (m_position.x >= 730)
		m_position.x = 730;
	else if (m_position.x <= -28)
		m_position.x = -28;

	if (m_position.y <= -14)
		m_position.y = -14;
	else if (m_position.y >= 543)
		m_position.y = 543;
	//za obj velikost 32*/

	//za obj velikost 16x32
	if (m_position.x >= 757)
		m_position.x = 757;
	else if (m_position.x <= -5)
		m_position.x = -5;

	if (m_position.y <= -1)
		m_position.y = -1;
	else if (m_position.y >= 543)
		m_position.y = 543;
	//za obj velikost 16x32
}

/*bool Predmet::collisonDetection(Hudoba* a[10])
{
	int xdist = 0;
	int ydist = 0;
	int xhudoba[10];
	int yhudoba[10];
	int razdalja[10];

	//sredina texture (Player1, Enemy1)
	xdist = (m_position.x + 16) / 2;
	ydist = (m_position.y + 32) / 2;

	for (int i = 0; i < 10; i++)
	{
		//sredina texture od hudobe
		xhudoba[i] = (a[i]->getx + 16) / 2;
		yhudoba[i] = (a[i]->gety + 16) / 2;

		razdalja[i] = //formula za razdaljo med dvema toèkama
	}

	for (int i = 0; i < 10; i++)
	{
		if(//razdalja  >= 16)
			/*std::cout << "collision" << std::endl;
			
	}
}*/

Igralec::Igralec(const char* path, float scale) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 16;
	m_srcRect.h = 32;

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

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

Hudoba::Hudoba(const char* path, float scale) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 16;
	m_srcRect.h = 32;

	m_position.x = rand() % 759 - 28;
	m_position.y = rand() % 557 - 14;

	std::cout << m_position.x << ", " << m_position.y << std::endl;

	m_scale = scale;
}

void Hudoba::update()
{
	Predmet::border();
	posUpdate();
}

void Hudoba::posUpdate()
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

Predmet::~Predmet() {}
Igralec::~Igralec() {}
Hudoba::~Hudoba() {}