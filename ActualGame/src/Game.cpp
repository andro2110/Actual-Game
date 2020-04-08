#include "Game.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include "HomeScreen.h"
#include "Text.h"
#include "Predmet.h"
#include "Files.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::homesc = 1;

Game::Game() {}
Game::~Game() {}

Map* map;
Igralec* player;
Homesc* game;
Datoteka* dat;
std::vector<std::unique_ptr<Hudoba>> hudoba;
std::vector<std::unique_ptr<Staroselec>> starina;
bool fl = 0;

void Game::Init(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	m_Framecount = 0;

	TTF_Init();
	SDL_Init(SDL_INIT_EVERYTHING);
	if (SDL_Init(SDL_INIT_EVERYTHING) == false) {

		m_window = SDL_CreateWindow(title, x, y, w, h, flags);

		Game::renderer = SDL_CreateRenderer(m_window, -1, 0);
		SDL_SetRenderDrawColor(Game::renderer, 33, 110, 54, 255);

		m_IsRunning = true;
	}
	else {
		m_IsRunning = false;
		std::cout << "Failed to run" << std::endl;
	}


	//od tukej naprej pisi kodo
	game = new Homesc();

	map = new Map();

	player = new Igralec("Assets/PlayerSprite.png", 2.0f);
	/*hudoba.push_back(std::unique_ptr<Hudoba>(std::make_unique<Hudoba>("Assets/EnemySprite.png", 1.5f, lvl)));
	starina.push_back(std::unique_ptr<Staroselec>(std::make_unique<Staroselec>("Assets/StaroselecSprite.png", 1.5f)));*/
	
	dat = new Datoteka;
}

void Game::HandleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_IsRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if ((Game::event.button.x > 35 && Game::event.button.x < 110) && (Game::event.button.y > 400 && Game::event.button.y < 430))//play pozicija
			m_play = 1;

		else if ((event.button.x > 666 && event.button.x < 735) && (event.button.y > 515 && event.button.y < 545))//quit
			m_IsRunning = false;

		game->preveri();
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)//preverja tipke za pavzo
		{
		case SDLK_ESCAPE:
		case SDLK_p:
			if (p == 0)
			{
				player->pavza(1);
				for (auto& h : hudoba)
					h->pavza(1);
				for (auto& s : starina)
					s->pavza(1);
				map->pavza(1);
				p = 1;
			}
			else if (p == 1)
			{
				player->pavza(0);
				for (auto& h : hudoba)
					h->pavza(0);
				for (auto& s : starina)
					s->pavza(0);
				map->pavza(0);
				p = 0;
			}
		default:
			break;
		}

	default:
		break;
	}
}

void Game::Update()
{
	if (m_play == true)//preverja
	{
		stej++;
		if (lvl == 1)//preverja kdaj je konec igre
		{
			game->getVrsta(5);//lvl1 slika
		}
		else if (lvl == 2)
		{
			game->getVrsta(6);//lvl2 slika
		}
		else if (lvl == 3)
		{
			game->getVrsta(7);//lvl3 slika
		}
		else
		{
			if (lvl == 4)
				game->getVrsta(8);
			else if(map->preveriProcente() >= 70)
				game->getVrsta(4);

			hudoba.clear();
			starina.clear();
			map->clear();
			dat->vpisiPod(map->vrniScore());
			dat->preberi();
			dat->sortiraj();
			dat->brisi();
			dat->topPet();

			homesc = 1;
			lvl = 1;
			m_play = 0;
			m_Framecount = 0;
		}

		if (stej % 120 == 0)//po dveh sekundah se zacne igra
		{
			stej = 0;
			m_play = 0;
			homesc = false;
		}
	}
	else if (homesc == false)//preverja med igro
	{
		if (m_Framecount % 120 == 0)//level traja 20 sekund
		{
			lvl++;

			m_play = 1;
			homesc = true;
			m_Framecount = 0;

			hudoba.clear();
			starina.clear();
			map->clear();
			map->nextlvl(lvl);

		}
	}

	if (homesc == false)
	{
		player->update();

		for (auto& h : hudoba)
		{
			h->update();
		}

		map->pogasiPozar(player);
		map->correctmap(hudoba);

		switch (lvl)
		{
		case 1:
			m_delayHudoba = 180;
			m_delayStarina = 180;
			break;
			
		case 2:
			m_delayHudoba = 120;
			m_delayStarina = 200;
			break;

		case 3:
			m_delayHudoba = 90;
			m_delayStarina = 240;
			break;

		default:
			break;
		}

		if (m_Framecount % m_delayHudoba == 0 && p == 0)//spawn hudobe
			hudoba.push_back(std::unique_ptr<Hudoba>(std::make_unique<Hudoba>("Assets/EnemySprite.png", 1.5f, lvl)));

		if(m_Framecount % m_delayStarina == 0 && p == 0)//spawn staroselcev
			starina.push_back(std::unique_ptr<Staroselec>(std::make_unique<Staroselec>("Assets/StaroselecSprite.png", 1.5f)));

		if (hudoba.size() != 0)
		{
			for (int i = 0; i < hudoba.size(); i++)
			{
				if (player->checkCollision(hudoba[i]->vrniDest(), hudoba[i]->vrniSrc()))//player x hudoba collision
					hudoba.erase(hudoba.begin() + i);//zbrise hudobo
			}

			for (auto& s : starina)
				for (int h = 0; h < hudoba.size(); h++)
					if (s->checkCollision(hudoba[h]->vrniDest(), hudoba[h]->vrniSrc()))//staroselec x hudoba collison
						hudoba.erase(hudoba.begin() + h);

			for (auto& s : starina)
			{
				s->slediHudobi(hudoba);//staroselec zacne slediti hudobi
			}
		}

		if (starina.size() != 0)
		{
			for (int i = 0; i < starina.size(); i++)
			{
				if (starina[i]->getLife() == 0)//preverja kdaj zbrise hudobo
					starina.erase(starina.begin() + i);
			}
		}

		map->getStaroselec(starina);

		for (auto& s : starina)
			s->update();

		if (p == 0)
			m_Framecount++;
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	/* Tuki se rendera: */
	if (homesc)
	{
		game->draw();
	}
	else
	{
		map->drawMap();

		player->render();

		for (auto& h : hudoba)
			h->render();

		for (auto& s : starina)
			s->render();
	}

//	test->draw();

	SDL_RenderPresent(Game::renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();

	std::cout << "Game finished" << std::endl;
}