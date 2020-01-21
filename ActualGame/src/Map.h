#pragma once
#include "TextureManager.h"
#include "Predmet.h"

class Map
{
public:
	Map();
	~Map();

	void loadMap(int array[20][25]);
	void drawMap();
	void correctMap(Hudoba *a, bool test);
	bool returnTest() { return m_test; }

private:
	SDL_Rect m_srcRect, m_destRect;
	SDL_Texture* m_normalTree;
	SDL_Texture* m_fireTree;
	SDL_Texture* m_stor;

	bool m_test;

	int m_map[20][25];
};
