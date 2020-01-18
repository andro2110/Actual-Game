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
	void correctMap(Hudoba *a);

private:
	SDL_Rect m_srcRect, m_destRect;
	SDL_Texture* m_normalTree;
	SDL_Texture* m_fireTree;

	int m_map[20][25];
};
