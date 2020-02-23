#include "Game.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include "HomeScreen.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::homesc = 1;

Game::Game() {}
Game::~Game() {}

Map* map;
Igralec* player;
Homesc* game;

std::vector<std::unique_ptr<Hudoba>> hudoba;
std::vector<std::unique_ptr<Staroselec>> starina;

void Game::Init(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	m_Framecount = 0;

	SDL_Init(SDL_INIT_EVERYTHING);
	if (SDL_Init(SDL_INIT_EVERYTHING) == false) {
		std::cout << "SubSystems Initialized" << std::endl;

		m_window = SDL_CreateWindow(title, x, y, w, h, flags);

		if (m_window != NULL)
			std::cout << "Window initialized" << std::endl;

		Game::renderer = SDL_CreateRenderer(m_window, -1, 0);

		if (Game::renderer) {
			SDL_SetRenderDrawColor(Game::renderer, 33, 110, 54, 255);
			std::cout << "Renderer initialized" << std::endl;
		}

		m_IsRunning = true;
		std::cout << "Is running" << std::endl;
	}
	else {
		m_IsRunning = false;
		std::cout << "Failed to inicialize" << std::endl;
	}

	//od tukej naprej pisi kodo
	game = new Homesc();

	map = new Map();

	player = new Igralec("Assets/Player.png", 2.0f);

	/*hudoba.push_back(std::unique_ptr<Hudoba>(std::make_unique<Hudoba>("Assets/Enemy.png", 2.0f)));
	starina.push_back(std::unique_ptr<Staroselec>(std::make_unique<Staroselec>("Assets/Staroselec.png", 2.0f)));*/

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
		{
			m_play = 1;
		}

		else if ((event.button.x > 666 && event.button.x < 735) && (event.button.y > 515 && event.button.y < 545))//quit
			m_IsRunning = false;

		game->preveri();
		break;

	default:
		break;
	}
}

void Game::Update()
{
	if (m_play == true)//preverja
	{
		stej++;
		if (lvl == 1)
			game->getVrsta(5);//lvl2 slika
		else if (lvl == 3)
			game->getVrsta(7);//lvl3 slika
		else if(lvl == 2)
			game->getVrsta(6);//pojavi se lvl1 slika

		if (stej % 120 == 0)//po dveh sekundah se zacne igra
		{
			stej = 0;
			m_play = 0;
			homesc = false;
		}
	}
	else if(homesc == false)//preverja med igro
	{
		if (m_Framecount % 1200 == 0)//level traja 20 sekund
		{
			lvl++;

			m_play = 1;
			homesc = true;
			m_Framecount = 0;

			hudoba.clear();
			starina.clear();
			map->nextlvl(lvl);
		}
	}

	if (homesc == false)
	{
		player->update();

		for (auto& h : hudoba)
			h->update();

		map->pogasiPozar(player);
		map->correctmap(hudoba);

		if (m_Framecount % 300 == 0)//hudobe & staroselci se spawnajo na 5 sekund
		{
			hudoba.push_back(std::unique_ptr<Hudoba>(std::make_unique<Hudoba>("Assets/Enemy.png", 2.0f)));
			starina.push_back(std::unique_ptr<Staroselec>(std::make_unique<Staroselec>("Assets/Staroselec.png", 2.0f)));
		}

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
		if (map->preveriProcente() >= 70)//dej na 70 ||game over
		{
			game->getVrsta(4);
			homesc = 1;

			std::cout << "Tocke: " << map->vrniScore() << std::endl;
		}

		else if (lvl == 4)
		{
			game->getVrsta(8);
			homesc = true;
		}
		map->drawMap();

		player->render();

		for (auto& h : hudoba)
			h->render();

		for (auto& s : starina)
			s->render();
	}

	SDL_RenderPresent(Game::renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();

	std::cout << "Game finished" << std::endl;
}