#include "Game.h"
#include "Map.h"
#include <iostream>
#include <vector>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game() {}
Game::~Game() {}

Map* map;
Igralec* player;

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
	map = new Map();

	player = new Igralec("Assets/Player.png", 2.0f);
	
	hudoba.push_back(std::unique_ptr<Hudoba>(std::make_unique<Hudoba>("Assets/Enemy.png", 2.0f)));
	starina.push_back(std::unique_ptr<Staroselec>(std::make_unique<Staroselec>("Assets/Staroselec.png", 2.0f)));
}

void Game::HandleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_IsRunning = false;
		break;

	default:
		break;
	}
}

void Game::Update()
{
	player->update();

	for (auto& h : hudoba)
		h->update();

	map->pogasiPozar(player);
	map->correctmap(hudoba);


	/*if (m_Framecount % 200 == 0)
	{
		hudoba.push_back(std::unique_ptr<Hudoba>(std::make_unique<Hudoba>("Assets/Enemy.png", 2.0f)));
		starina.push_back(std::unique_ptr<Staroselec>(std::make_unique<Staroselec>("Assets/Staroselec.png", 2.0f)));
	}*/

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
			std::cout << "lajf: " << starina[i]->getLife() << std::endl;
			if (starina[i]->getLife() == 0)
				starina.erase(starina.begin() + i);
		}

	}
	
	map->getStaroselec(starina);

	for (auto& s : starina)
		s->update();

	/*if (map->preveriProcente() >= 70)
		m_IsRunning = false;*/

	m_Framecount++;
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	/* Tuki se rendera: */
	map->drawMap();

	player->render();
	
	for (auto& h : hudoba)
		h->render();

	for (auto& s : starina)
		s->render();

	SDL_RenderPresent(Game::renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();

	std::cout << "Game finished" << std::endl;
}