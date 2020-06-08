#include "Predmet.h"

Predmet::Predmet(const char* path, float scale) {}

void Predmet::update() {}

void Predmet::render()
{
	SDL_RenderCopy(Game::renderer, m_texture, &m_srcRect, &m_destRect);
}

void Predmet::posUpdate() {}

void Predmet::border()
{
	if (m_position.x < -m_srcRect.w)
		m_position.x = -m_srcRect.w;
	else if (m_position.x > (800 - m_srcRect.w))
		m_position.x = 800 - m_srcRect.w;

	if (m_position.y < -m_srcRect.h)
		m_position.y = -m_srcRect.h;
	else if (m_position.y > (640 - m_srcRect.h))
		m_position.y = 640 - m_srcRect.h;
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

	if ((m_position.x + m_srcRect.w) > dest.x && m_position.x < dest.x + src.w && m_position.y + m_srcRect.h > dest.y && m_position.y < dest.y + src.h)
		return true;
	else
		return false;
}

void Predmet::pavza(bool pavza)
{
	p = pavza;
}

Igralec::Igralec(const char* path, float scale) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 24;
	m_srcRect.h = 28;

	m_speed = 3;

	m_position.x = 0;
	m_position.y = 0;
	
	m_lastpos.x = m_position.x;
	m_lastpos.y = m_position.y;

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
	if (Game::event.type == SDL_KEYDOWN && p != 1)
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

	if (Game::event.type == SDL_KEYUP && p != 1)
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

void Igralec::preberi()
{
	std::ifstream beri("Replay.bin");
	struct Pos tmp;

	if (beri.is_open())
	{
		while (beri.read((char*)&tmp, sizeof(tmp)))
		{
			m_sm.push_back(tmp);
		}
	}

	beri.close();
}

void Igralec::resume(Vec2 pos)
{
	m_position.x = pos.x;
	m_position.y = pos.y;
}

void Igralec::updateRep()
{
	m_position.x = 0;
	m_position.y = 0;
	for (int i = 0; i < m_sm.size(); i++)
	{
		m_srcRect.x = m_srcRect.w * static_cast<int>((SDL_GetTicks() / 200) % 1);
		m_srcRect.y = 0;

		m_position.x += m_sm[i].x * 2;
		m_position.y += m_sm[i].y * 2;

		m_destRect.x = m_position.x;
		m_destRect.y = m_position.y;

		m_destRect.w = m_srcRect.w * m_scale;
		m_destRect.h = m_srcRect.h * m_scale;
	}

}

void Igralec::superSanic(bool mode)
{
	if (m_timer < 180 && p == 0 && mode == 1)
	{
		m_speed = 5;
		m_timer++;
		m_end = 0;
	}
	else
	{
		m_speed = 3;
		m_timer = 0;
		m_end = 1;
	}
}

void Igralec::spremeniRend()
{
	if (m_sanicMode == 5)
	{
		SDL_SetRenderDrawColor(Game::renderer, r, g, b, 255);
		m_sanicMode = 0;
	}
	else
	{
		m_sanicMode++;
		r = rand() % (255) + 1;
		g = rand() % (255) + 1;
		b = rand() % (255) + 1;
	}
}

Hudoba::Hudoba(const char* path, float scale, int lvl) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 32;
	m_srcRect.h = 32;

	m_position.x = rand() % (800 - m_srcRect.w) + m_srcRect.w;
	m_position.y = rand() % (640 - m_srcRect.h) + m_srcRect.h;

	m_randx = rand() % (800 - m_srcRect.w) + m_srcRect.w;
	m_randy = rand() % (640 - m_srcRect.h) + m_srcRect.h;
	
	m_speed = 1;

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
	/*m_position.x += m_smer.x * m_speed;
	m_position.y += m_smer.y * m_speed;*/

	m_srcRect.x = m_srcRect.w * static_cast<int>((SDL_GetTicks() / 180) % 3);

	if(m_pravoMesto == 1)//ce je na pravem mestu ni vec animiran
		m_srcRect.x = m_srcRect.w;
	
	m_srcRect.y = m_zamik;

	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

void Hudoba::premakni()
{
	if (m_position.x > m_randx && p != 1)
	{
		m_zamik = 32;
		m_position.x--;
	}
	else if (m_position.x < m_randx && p != 1)
	{
		m_zamik = 64;
		m_position.x++;
	}

	if (m_position.y > m_randy && p != 1)
	{
		m_zamik = 96;
		m_position.y--;
	}
	else if (m_position.y < m_randy && p != 1)
	{
		m_zamik = 0;
		m_position.y++;
	}
}

void Hudoba::preveriPos()
{
	if (m_position.x == m_randx && m_position.y == m_randy)
	{
		m_pravoMesto = 1;
		m_framecount++;
		if (m_framecount == 120)
		{
			m_randx = rand() % (800 - m_srcRect.w) + m_srcRect.w;
			m_randy = rand() % (640 - m_srcRect.h) + m_srcRect.h;

			m_framecount = 0;
		}
	}
	else
		m_pravoMesto = 0;
}

Staroselec::Staroselec(const char* path, float scale) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 32;
	m_srcRect.h = 32;

	m_position.x = rand() % (800 - m_srcRect.w) + m_srcRect.w;
	m_position.y = rand() % (640 - m_srcRect.h) + m_srcRect.h;

	m_nasMestox = rand() % 768 + 33;
	m_nasMestoy = rand() % 608 + 33;

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
	m_srcRect.x = m_srcRect.w * static_cast<int>((SDL_GetTicks() / 180) % 3);

	if (m_pravoMesto == 1)
		m_srcRect.x = m_srcRect.w;
	m_srcRect.y = m_zamik;

	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

void Staroselec::premakni()
{
	if (m_position.x > m_nasMestox && p != 1)
	{
		m_zamik = 32;
		m_position.x--;
	}
	else if (m_position.x < m_nasMestox && p != 1)
	{
		m_zamik = 64;
		m_position.x++;
	}

	if (m_position.y < m_nasMestoy && p != 1)
	{
		m_zamik = 0;
		m_position.y++;
	}
	else if (m_position.y > m_nasMestoy&& p != 1)
	{
		m_zamik = 96;
		m_position.y--;
	}
}

void Staroselec::getHudoba(int x, int y)
{
	m_nasMestox = x;
	m_nasMestoy = y;
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
				m_nasMestox = rand() % (800 - m_srcRect.w) + m_srcRect.w;
				m_nasMestoy = rand() % (640 - m_srcRect.h) + m_srcRect.h;//mesto gre spet na random, ko pride do pozara

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
				m_nasMestox = rand() % (800 - m_srcRect.w) + m_srcRect.w;
				m_nasMestoy = rand() % (640 - m_srcRect.h) + m_srcRect.h;//mesto gre spet na random

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

Diamantek::Diamantek(const char* path, float scale) : Predmet(path, scale)
{
	m_texture = TextureManager::LoadTexture(path);

	m_srcRect.w = 15;
	m_srcRect.h = 15;

	m_position.x = rand() % (800 - m_srcRect.w) + m_srcRect.w;
	m_position.y = rand() % (640 - m_srcRect.h) + m_srcRect.h;

	m_scale = scale;
}

void Diamantek::update()
{
	m_destRect.x = m_position.x;
	m_destRect.y = m_position.y;

	m_destRect.w = m_srcRect.w * m_scale;
	m_destRect.h = m_srcRect.h * m_scale;
}

Predmet::~Predmet() {}
Igralec::~Igralec() {}
Hudoba::~Hudoba() {}
Staroselec::~Staroselec() {}
Diamantek::~Diamantek() {}