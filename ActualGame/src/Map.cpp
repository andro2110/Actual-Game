 #include "Map.h"

int lvl[20][25] = { 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

Map::Map()
{
	m_normalTree = TextureManager::LoadTexture("Assets/Drevo.png");
	m_fireTree = TextureManager::LoadTexture("Assets/Ogenj.png");
	m_stor = TextureManager::LoadTexture("Assets/Stor.png");
	m_zazgan = TextureManager::LoadTexture("Assets/Zazgano.png");

	loadMap(lvl);

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.h = 32;
	m_srcRect.w = 32;

	m_destRect.h = 32;
	m_destRect.w = 32;
	m_destRect.x = 0;
	m_destRect.y = 0;
}

Map::~Map() {}

void Map::loadMap(int arr[20][25])
{
	for (int vrstica = 0; vrstica < 20; vrstica++)
	{
		for (int stolpec = 0; stolpec < 25; stolpec++)
		{
			m_map[vrstica][stolpec] = arr[vrstica][stolpec];
		}
	}
}

void Map::drawMap()
{
	int type = 0;
		
	for (int vrstica = 0; vrstica < 20; vrstica++)
	{
		for (int stolpec = 0; stolpec < 25; stolpec++)
		{
			type = m_map[vrstica][stolpec];

			m_destRect.x = stolpec * 32;
			m_destRect.y = vrstica * 32;

			switch (type)
			{
			case 0:
				TextureManager::Draw(m_normalTree, m_srcRect, m_destRect);
				break;

			case 1:
				TextureManager::Draw(m_fireTree, m_srcRect, m_destRect);
				break;
				
			case 2:
				TextureManager::Draw(m_stor, m_srcRect, m_destRect);
				break;

			case 3:
				TextureManager::Draw(m_zazgan, m_srcRect, m_destRect);
				break;
			default:
				break;
			}
		}
	}
	randomFire();
	razsiriOgenj();
}

void Map::correctmap(std::vector<std::unique_ptr<Hudoba>> &a)
{
	for (int i = 0; i < a.size(); i++)
	{
		int xpos = floor(a[i]->getx() / 32);
		int ypos = floor(a[i]->gety() / 32) + 3;

		if (a[i]->pravoMesto() == true && m_map[ypos][xpos] != 1 && m_map[ypos][xpos] != 2 && m_map[ypos][xpos] != 3)
		{
			m_map[ypos][xpos] = 2;
			m_uniceno++;
		}
	}
}

void Map::randomFire()
{
	int xpos;
	int ypos;

	if (m_spawnFire == m_delay)
	{
		xpos = floor((rand() % 640 + 0) / 32);
		ypos = floor((rand() % 800 + 0) / 32);

		if (m_map[xpos][ypos] != 2)
		{
			m_map[xpos][ypos] = 1;
			m_uniceno++;
		}

		m_spawnFire = 0;
	}
	m_spawnFire++;
}

void Map::pogasiPozar(Igralec* igralec)
{
	int xpos = floor(igralec->getx() / 32);
	int ypos = floor(igralec->gety() / 32) + 3;

	if (m_map[ypos][xpos] == 1)
	{
		m_map[ypos][xpos] = 3;
		m_score++;
	}
}

void Map::izracun()
{
	int procent = (100 * m_uniceno) / 500;
	std::cout << "Uniceno (%): " << procent << " Tocke: " << m_score << std::endl;
}

void Map::getStaroselec(std::vector<std::unique_ptr<Staroselec>>& a)
{
	for (int i = 0; i < a.size(); i++)
	{
		int x, y;
		bool test;
		test = a[i]->pravoMesto();

		Vec2 tmp;
		tmp.x = (a[i]->gety() + 15 * 3.0f);
		tmp.y = (a[i]->getx() + 5 * 3.0f);

		x = tmp.x / 32;
		y = tmp.y / 32; // pretvorba v indexe tabele

		for (int range = 0; range < 4; range++)
		{
			if (m_map[x][y + range] == 1)
			{
				a[i]->changePos((y + range) * 32, x * 32, 1); //ciljna pozicija
				
				if (a[i]->pravoMesto() == true)
				{
					m_map[y][x] = 3;
				}
			}
			else
				a[i]->premakni();
		}
		std::cout << "Map: " << a[i]->pravoMesto() << std::endl;
	}
}

void Map::razsiriOgenj()
{
	if (m_razsiri == m_razsiriDelay)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (m_map[i][j] == 1)
				{
					int smer;
					smer = rand() % 4 + 1;
					
					switch (smer)
					{
					case 1:
						if (m_map[i][j + 1] != 1)
						{
							m_map[i][j + 1] = 1;
							m_uniceno++;

							if (j + 1 >= 24)
								break;
							else
								j += 1;
						}
						break;

					case 2:
						if (m_map[i + 1][j] != 1)
						{
							m_map[i + 1][j] = 1;
							m_uniceno++;

							if (i + 1 >= 19)
								break;
							else
								i += 1;
						}
						break;

					case 3:
						if (j - 1 < 0)
							break;

						else
						{
							if (m_map[i][j - 1] != 1)
							{
								m_map[i][j - 1] = 1;
								j += 1;
								m_uniceno++;
							}
						}
						break;

					case 4:
						if (i - 1 < 0)
							break;

						else
						{
							if (m_map[i - 1][j] != 1)
							{
								m_map[i - 1][j] = 1;
								i -= 1;
								m_uniceno++;
							}
						}
						break;

					default:
						break;
					}

					m_razsiri = 0;
				}
			}
		}
	}
	m_razsiri++;
}

int Map::preveriProcente()
{
	int procent = (100 * m_uniceno) / 500;

	return procent;
}