#pragma once
#include "TextureManager.h"
#include "Predmet.h"
#include <vector>

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

private:
	SDL_Rect m_srcRect, m_destRect;
	SDL_Texture* m_normalTree;
	SDL_Texture* m_fireTree;
	SDL_Texture* m_stor;
	SDL_Texture* m_zazgan;

	bool m_test;
	int m_spawnFire = 0;
	int m_counterIgralec = 0;
	int m_delay = 200;
	int m_razsiri = 0;
	int m_razsiriDelay = 300;
	
	int score = 0;
	int uniceno = 0;

	int m_map[20][25];
};
