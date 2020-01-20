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
Hudoba* hudoba;
Staroselec* starina[3];

//std::vector<Hudoba>* hudoba;

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

	player = new Igralec("Assets/Player.png", 3.0f);
	hudoba = new Hudoba("Assets/Enemy.png", 3.0f);
	for (int i = 0; i < 3; i++)
	{
		starina[i] = new Staroselec("Assets/Staroselec.png", 3.0f);
		starina[i]->getHudoba(hudoba);
	}
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
	hudoba->update();
	for (int i = 0; i < 3; i++)
	{
		starina[i]->update();
	}

	m_Framecount++;
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	/* Tuki se rendera: */
	map->drawMap();

	player->render();
	hudoba->render();
	for (int i = 0; i < 3; i++)
	{
		starina[i]->render();
	}
	map->correctMap(hudoba);

	SDL_RenderPresent(Game::renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();

	std::cout << "Game finished" << std::endl;
}
