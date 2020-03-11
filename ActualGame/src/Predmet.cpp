#include "Predmet.h"

Predmet::Predmet(const char* path, float scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w;
	m_srcRect.h ;

	m_position.x;
	m_position.y;

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

void Predmet::border()
{
	//za velikost 10x30
	if (m_position.x < -5)
		m_position.x = -6;
	else if (m_position.x > 750)
		m_position.x = 750;

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

	m_srcRect.w = 24;
	m_srcRect.h = 28;

	m_speed = 3;

	m_position.x = 0;
	m_position.y = 0;

	m_scale = scale;
}

void Igralec::update()
{
	premik();
	Predmet::border();

	posUpdate();
}

void Igralec::premik()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_a:
			m_smer.x = -1;
			m_zamik = 128;
			break;
		case SDLK_w:
			m_smer.y = -1;
			m_zamik = 64;
			break;
		case SDLK_s:
			m_zamik = 32;
			m_smer.y = 1;
			break;
		case SDLK_d:
			m_zamik = 96;
			m_smer.x = 1;
		default:
			break;
		}
	}

	if (Game::event.type == SDL_KEYUP && Game::event.type != SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_a:
			m_smer.x = 0;
			m_zamik = 0;
			break;
		case SDLK_w:
			m_zamik = 0;
			m_smer.y = 0;
			break;
		case SDLK_s:
			m_zamik = 0;
			m_smer.y = 0;
			break;
		case SDLK_d:
			m_zamik = 0;
			m_smer.x = 0;
		default:
			break;
		}
	}
}

void Igralec::posUpdate()
{
	m_srcRect.x = m_srcRect.w * static_cast<int>((SDL_GetTicks() / 200) % 4);
	m_srcRect.y = m_zamik;

	m_position.x += m_smer.x * m_speed;
	m_position.y += m_smer.y * m_speed;

	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

Hudoba::Hudoba(const char* path, float scale, int lvl) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 10;
	m_srcRect.h = 30;

	m_position.x = rand() % 758 + 3;
	m_position.y = rand() % 520 + 3;

	m_randx = rand() % 758 + 3;
	m_randy = rand() % 520 + 3;

	/*switch (lvl)
	{
	case 1:
		m_speed = 1.25;
		break;
	case 2:
		m_speed = 3.25;
		break;
	default:
		break;
	}*/

	std::cout << lvl<< std::endl;

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
	m_position.x += m_smer.x * m_speed;
	m_position.y += m_smer.y * m_speed;

	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

void Hudoba::premakni()
{
	if (m_position.x >= m_randx)
		m_smer.x = -1;
	else if (m_position.x <= m_randx)
		m_smer.x = 1;

	if (m_position.y >= m_randy)
		m_smer.y = -1;
	else if (m_position.y <= m_randy)
		m_smer.y = 1;
}

void Hudoba::preveriPos()
{
	if (m_position.x == m_randx && m_position.y == m_randy)
	{
		m_pravoMesto = 1;
		m_framecount++;
		if (m_framecount == 120)
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
		m_position.x -= 1;
	else if (m_position.x < m_nasMestox)
		m_position.x += 1;

	if (m_position.y < m_nasMestoy)
		m_position.y += 1;
	else if (m_position.y > m_nasMestoy)
		m_position.y -= 1;
}

void Staroselec::getHudoba(int x, int y)
{
	m_hux = x;
	m_huy = y;
}

void Staroselec::changePos(int x, int y)//dobi koordinate, kam naj se naslednje premakne
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

			if (m_framecount == 120)//dve sekundi
			{
				m_nasMestox = rand() % 750 + 5;
				m_nasMestoy = rand() % 520 + 5;//mesto gre spet na random, ko pride do pozara

				m_life--;
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

			if (m_framecount == 60)
			{
				m_nasMestox = rand() % 750 + 5;
				m_nasMestoy = rand() % 520 + 5;//mesto gre spet na random

				m_life--;
				m_framecount = 0;
			}
		}
		else
			m_pravoMesto = 0;
	}
}

void Staroselec::slediHudobi(std::vector<std::unique_ptr<Hudoba>>& hudobe)
{
	if (hudobe.size() > 0)
		for (int i = 0; i < hudobe.size(); i++)
		{
			int razdalja = 0;

			int t1x = m_destRect.x;//sredinska x koordinata staroselca
			int t1y = m_destRect.y;//sredinska y koordinata staroselca

			int t2x = hudobe[i]->vrniDest().x;//sredinska x koordinata hudobe z indexom i
			int t2y = hudobe[i]->vrniDest().y;//sredinska y koordinata hudobe z indexom i

			razdalja = sqrt(pow((t2x - t1x), 2) + pow((t2y - t1y), 2));//racunanje razdalje

			if (razdalja <= 100)
			{
				changePos(hudobe[i]->getx(), hudobe[i]->gety());//staroselec spremeni ciljne koordinate, èe je hudoba dovolj blizu
			}
		}
}

Predmet::~Predmet() {}
Igralec::~Igralec() {}
Hudoba::~Hudoba() {}
Staroselec::~Staroselec() {}