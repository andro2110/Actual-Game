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

private:
	SDL_Rect m_srcRect, m_destRect;
	SDL_Texture* m_normalTree;
	SDL_Texture* m_fireTree;
	SDL_Texture* m_stor;

	bool m_test;
	int m_counter = 0;

	int m_map[20][25];
};
