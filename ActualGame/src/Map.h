#pragma once
#include "TextureManager.h"
#include "Predmet.h"
//#include <vector>
#include <cmath>

class Map
{
public:
	Map();
	~Map();

	void loadMap(int array[20][25]);
	void drawMap();
	void correctmap(std::vector<std::unique_ptr<Hudoba>> &a);
	void randomFire();
	void pogasiPozar(Igralec *igralec);
	void razsiriOgenj();
	void izracun();
	void getStaroselec(std::vector<std::unique_ptr<Staroselec>> &a);
	
	int preveriProcente();

private:
	SDL_Rect m_srcRect, m_destRect;
	SDL_Texture* m_normalTree;
	SDL_Texture* m_fireTree;
	SDL_Texture* m_stor;
	SDL_Texture* m_zazgan;

	bool m_test;
	int m_spawnFire = 0;
	int m_counterIgralec = 0;
	int m_delay = 100;
	int m_razsiri = 0;
	int m_razsiriDelay = 300;
	
	int m_score = 0;
	int m_uniceno = 0;

	int m_map[20][25];
};
