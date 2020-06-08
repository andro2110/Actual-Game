#include "Game.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include "HomeScreen.h"
#include "Predmet.h"
#include "Files.h"
#include "Besedilo.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

int sec = 0;
int m_cas = 1200;//nastavi trajanje lvla
bool seVpisuje;
int lvl = 0;
bool igraj;
int tmp = 0;
int score;
int sanic = 0;

Game::Game() {}
Game::~Game() {}

Map* map;
Igralec* player;
Homesc* game;

Datoteka* dat;
Datoteka* rep;
Datoteka* save;

Text* tocke;
Text* procenti;
Text* cas;
Text* bes1;
Text* ime;
Text* bes2;

std::vector<std::unique_ptr<Hudoba>> hudoba;
std::vector<std::unique_ptr<Staroselec>> starina;
std::vector<std::unique_ptr<Diamantek>> diamantek;

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
	diamantek.push_back(std::unique_ptr<Diamantek>(std::make_unique<Diamantek>("Assets/Diamond.png", 2.0f)));
	
	dat = new Datoteka;
	rep = new Datoteka;
	save = new Datoteka;

	tocke = new Text(40);
	procenti = new Text(40);
	cas = new Text(40);
	ime = new Text(40);
	bes1 = new Text(40);
	bes2 = new Text(40);

	if (dat->preveriDatoteke() == 1)
	{
		player->resume(dat->vrniPos());
		lvl = dat->vrniLvl();
		map->resume();
		sec = dat->vrniCas();
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

	case SDL_MOUSEBUTTONDOWN:

		if ((Game::event.button.x > 35 && Game::event.button.x < 120) && (Game::event.button.y > 365 && Game::event.button.y < 390))//play pozicija
		{
			m_mode = 1;
			stej = 0;
			game->getVrsta(1);
			tmp = 0;
		}

		if ((event.button.x > 660 && event.button.x < 765) && (event.button.y > 520 && event.button.y < 555))//quit
		{
			dat->pocistiDat();
			m_IsRunning = false;
		}

		 if (m_mode == 0 && (Game::event.button.x > 40 && Game::event.button.x < 160) && (Game::event.button.y > 530 && Game::event.button.y < 565))//replay
			game->getVrsta(9);

		if (m_mode == 2 && (Game::event.button.x > 280 && Game::event.button.x < 460) && (Game::event.button.y > 400 && Game::event.button.y < 450)) //save & quit
		{
			save->shrani(player->getx(), player->gety(), lvl, sec);//shrani podatke od igralca in lvl
			map->shrani();//shrani podatke o mapi (indexe, uniceno, tocke)
			m_IsRunning = false;
		}
		game->preveri();
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)//preverja tipke za pavzo
		{
		case SDLK_p:
			if (m_mode == 1 || m_mode == 2)
			{
				if (p == 0)
				{
					player->pavza(1);
					for (auto& h : hudoba)
						h->pavza(1);
					for (auto& s : starina)
						s->pavza(1);
					map->pavza(1);
					game->getVrsta(8);
					p = 1;
					m_mode = 2;
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
					m_mode = 1;
				}
			}
			break;
		default:
			break;
		}

	case SDL_MOUSEMOTION:
		//std::cout << event.motion.x << " " << event.motion.y << std::endl;

		break;
	default:
		break;
	}
}

void Game::Update()
{
	//std::cout << m_mode << std::endl;
	switch (m_mode)
	{
	case 0:
		stej++;
		
		if (stej % 120 == 0 && lvl > 0 && lvl < 4)//po dveh sekundah se zacne igra
		{
			stej = 0;
			sec = 0;

			m_mode = 1;
		}

		switch (lvl)
		{
		case 1:
			game->getVrsta(4);
			break;
		case 2:
			game->getVrsta(5);
			break;
		case 3:
			game->getVrsta(6);
			break;
		case 4:
			score = map->vrniScore();
			hudoba.clear();
			starina.clear();
			map->clear();
			map->nextlvl(1);
			sec = 0;

			lvl = 0;
			m_Framecount = 0;

			game->getVrsta(10);

			m_mode = 3;
			break;
		default:
			break;
		}
		
		//std::cout << stej << std::endl;
		break;

	case 1:
		if (m_Framecount % m_cas == 0)//level traja 20 sekund
		{
			m_mode = 0;
			m_Framecount = 0;
			lvl++;

			hudoba.clear();
			starina.clear();
			map->clear();
			map->nextlvl(lvl);
		}

		tocke->podatki(380, 0, std::to_string(map->vrniScore()), { 255, 255, 255, 220 }, { 171, 205, 56, 175 });
		procenti->podatki(0, 0, std::to_string(map->preveriProcente()), { 255, 255, 255, 175 }, { 216, 113, 65 , 215 });
		cas->podatki(750, 0, std::to_string((m_cas / 60) - sec), { 255, 255, 255, 175 }, { 56, 148, 221, 215 });
		player->update();

		for (auto& d : diamantek)
			d->update();

		for (auto& h : hudoba)
			h->update();

		map->pogasiPozar(player);
		map->posadi(player);
		map->correctmap(hudoba);

		switch (lvl)
		{
		case 1:
			m_delayHudoba = 180;
			m_delayStarina = 180;
			m_delayDiamantek = 1020;
			break;

		case 2:
			m_delayHudoba = 120;
			m_delayStarina = 200;
			m_delayDiamantek = 720;
			break;

		case 3:
			m_delayHudoba = 90;
			m_delayStarina = 240;
			m_delayDiamantek = 540;
			break;

		default:
			break;
		}

		if (m_Framecount % m_delayHudoba == 0 && p == 0)//spawn hudobe
			hudoba.push_back(std::unique_ptr<Hudoba>(std::make_unique<Hudoba>("Assets/EnemySprite.png", 1.5f, lvl)));

		if (m_Framecount % m_delayStarina == 0 && p == 0)//spawn taprijaznih
			starina.push_back(std::unique_ptr<Staroselec>(std::make_unique<Staroselec>("Assets/StaroselecSprite.png", 1.5f)));

		if (m_Framecount % m_delayDiamantek == 0 && p == 0)//spawn diamantka
			diamantek.push_back(std::unique_ptr<Diamantek>(std::make_unique<Diamantek>("Assets/Diamond.png", 2.0f)));

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

		for (int i = 0; i < diamantek.size(); i++)
		{
			if (diamantek[i]->checkCollision(player->vrniDest(), player->vrniSrc()))
			{
				diamantek.erase(diamantek.begin() + i);
				sanic = 1;
			}
		}
		player->superSanic(sanic);

		if (player->endSanic())
		{
			sanic = 0;
			SDL_SetRenderDrawColor(Game::renderer, 33, 110, 54, 125);
		}
		else
			player->spremeniRend();

		map->getStaroselec(starina);

		for (auto& s : starina)
			s->update();

		if (map->preveriProcente() >= 70)
			game->getVrsta(4);

		//rep->replay(player->vrniSmerx(), player->vrniSmery());//zapisuje koordinate v Replay.bin

		if (p == 0 && m_Framecount % 60 == 0)
			sec++;

		if (p == 0)
			m_Framecount++;

		break;
	case 3:
		break;
	default:
		break;
	}

	/*else if (homesc == false && replay == 1)
	{
		player->updateRep();
	}*/
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	/* Tuki se rendera: */
	switch (m_mode)
	{
	case 0:
		game->draw();
		break;

	case 1:
		/*if (lvl == 4)
		{
			
		}
		else if (map->preveriProcente() >= 70)
		{
			game->getVrsta(3);
			hudoba.clear();
			starina.clear();
			map->clear();
			dat->vpisiPod(map->vrniScore());
			dat->preberi();
			dat->sortiraj();
			dat->brisi();
			dat->izpis();
			map->nextlvl(1);

			m_mode = 0;
			lvl = 1;
			m_Framecount = 0;
		}*/

		map->drawMap();

		player->render();

		

		for (auto& h : hudoba)
			h->render();

		for (auto& s : starina)
			s->render();
		tocke->draw();
		procenti->draw();
		cas->draw();
		
		for (auto& d : diamantek)
			d->render();
		break;

	case 2://pauza
	case 3://konec igre
		game->draw();

		if (game->vpisano() && tmp == 0)
		{
			dat->vpisiPod(score, game->vrniIme());
			tmp = 1;
			game->getVrsta(11);
			game->zbrisiStr();
		}

		dat->preberi();
		dat->sortiraj();
		dat->brisi();
		break;
	default:
		break;
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