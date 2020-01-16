#pragma once
#include "TextureManager.h"

class Map
{
public:
	Map();
	~Map();

	void loadMap(int array[20][25]);
	void drawMap();

private:
	SDL_Rect m_srcRect, m_destRect;
	SDL_Texture* m_normalTree;

	int m_map[20][25];
};
