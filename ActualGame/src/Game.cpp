#include "Game.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include "HomeScreen.h"
#include "Text.h"
#include "Predmet.h"
#include "Files.h"
#include "Besedilo.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::homesc = 1;

Game::Game() {}
Game::~Game() {}

Map* map;
Igralec* player;
Homesc* game;

Datoteka* dat;
Datoteka* rep;

Text* tocke;
Text* procenti;
Text* pt1;
Text* pt2;
Text* pt3;

std::vector<std::unique_ptr<Hudoba>> hudoba;
std::vector<std::unique_ptr<Staroselec>> starina;
std::string str;

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
	//hudoba.push_back(std::unique_ptr<Hudoba>(std::make_unique<Hudoba>("Assets/EnemySprite.png", 1.5f, lvl)));
	//starina.push_back(std::unique_ptr<Staroselec>(std::make_unique<Staroselec>("Assets/StaroselecSprite.png", 1.5f)));
	
	dat = new Datoteka;
	rep = new Datoteka;

	tocke = new Text(40);
	procenti = new Text(40);
	pt1 = new Text(60);
	pt2 = new Text(40);
	pt3 = new Text(40);
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
		if ((Game::event.button.x > 35 && Game::event.button.x < 120) && (Game::event.button.y > 410 && Game::event.button.y < 440))//play pozicija
			m_play = 1;

		else if ((event.button.x > 660 && event.button.x < 765) && (event.button.y > 520 && event.button.y < 555))//quit
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
				game->getVrsta(9);
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
		case SDLK_r:
			if (p == 1)
				player->replay();
			break;
		default:
			break;
		}

	/*case SDL_MOUSEMOTION:
		std::cout << event.motion.x << " " << event.motion.y << std::endl;
		break;*/
	default:
		break;
	}
}

void Game::Update()
{
	if (m_play == true)
	{
		stej++;

		switch (lvl)
		{
		case 1:
			game->getVrsta(5);
			break;
		case 2:
			game->getVrsta(6);
			break;
		case 3:
			game->getVrsta(7);
			break;
		case 4:
			game->getVrsta(8);
			break;
		default:
			game->getVrsta(4);
			break;
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
		if (m_Framecount % 1200 == 0)//level traja 20 sekund
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
		tocke->podatki(380, 0, std::to_string(map->vrniScore()), { 255, 255, 255, 220 }, { 171, 205, 56, 175 });
		procenti->podatki(0, 0, std::to_string(map->preveriProcente()), { 255, 255, 255, 175 }, { 216, 113, 65 , 215 });
		player->update();

		for (auto& h : hudoba)
			h->update();

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

		if (map->preveriProcente() >= 70)
			game->getVrsta(4);

		rep->replay(player->getx(), player->gety());//zapisuje koordinate v Replay.bin

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
		if (lvl == 4)
		{
			game->getVrsta(8);
			hudoba.clear();
			starina.clear();
			map->clear();
			dat->vpisiPod(map->vrniScore());
			dat->preberi();
			dat->sortiraj();
			dat->brisi();
			dat->topPet();
			map->nextlvl(1);

			homesc = 1;
			lvl = 1;
			m_play = 0;
			m_Framecount = 0;
		}
		else if (map->preveriProcente() >= 70)
		{
			game->getVrsta(4);
			hudoba.clear();
			starina.clear();
			map->clear();
			dat->vpisiPod(map->vrniScore());
			dat->preberi();
			dat->sortiraj();
			dat->brisi();
			dat->topPet();
			map->nextlvl(1);

			homesc = 1;
			lvl = 1;
			m_play = 0;
			m_Framecount = 0;
		}


		map->drawMap();

		player->render();

		for (auto& h : hudoba)
			h->render();

		for (auto& s : starina)
			s->render();
		tocke->draw();
		procenti->draw();
		if (p == 1)
			pt1->shadedText(305, 230, "Pavza", { 255, 255, 255, 255 }, { 0, 0, 0, 255 });

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