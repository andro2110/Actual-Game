#include "Game.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include "HomeScreen.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game() {}
Game::~Game() {}

Map* map;
Igralec* player;
Homesc* game;


std::vector<std::unique_ptr<Hudoba>> hudoba;
std::vector<std::unique_ptr<Staroselec>> starina;

std::vector<int> test;

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

	//tuki pis kodo
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
		if ((event.button.x > 35 && event.button.x < 110) && (event.button.y > 400 && event.button.y < 430))//play pozicija
			homesc = 0;

		else if ((event.button.x > 35 && event.button.x < 455) && (event.button.y > 455 && event.button.y < 485))//credits
			game->getVrsta(2);

		else if ((event.button.x > 35 && event.button.x < 235) && (event.button.y > 515 && event.button.y < 545))//how to play
			game->getVrsta(3);

		else if ((event.button.x > 340 && event.button.x < 455) && (event.button.y > 555 && event.button.y < 580))//back
			game->getVrsta(1);

		else if ((event.button.x > 666 && event.button.x < 735) && (event.button.y > 515 && event.button.y < 545))//quit
			m_IsRunning = false;
		break;

	default:
		break;
	}
}

void Game::Update()
{
	if (homesc == false)
	{
		player->update();

		for (auto& h : hudoba)
			h->update();

		map->pogasiPozar(player);
		map->correctmap(hudoba);


		if (m_Framecount % 200 == 0)
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
				if (starina[i]->getLife() == 0)
					starina.erase(starina.begin() + i);
			}

		}

		map->getStaroselec(starina);

		for (auto& s : starina)
			s->update();
	}
	if (map->preveriProcente() >= 70)
		homesc = 1;
	std::cout << "Uniceno (%): " << map->preveriProcente() << std::endl;

	m_Framecount++;
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	/* Tuki se rendera: */
	if(homesc)
		game->draw();
	else
	{
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