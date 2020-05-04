#include "Files.h"

void Datoteka::vpisiPod(int tocke, std::string ime)
{
	std::ofstream pisi("Highscore.bin", std::ios::binary | std::ios::app);

	std::cout << tocke << std::endl;
	strcpy_s(m_pod.ime, ime.c_str());
	m_pod.tocke = tocke;

	pisi.write((char*)&m_pod, sizeof(m_pod));

	pisi.close();
}

void Datoteka::preberi()
{
	std::ifstream beri("Highscore.bin", std::ios::binary);

	if (beri.is_open())
	{
		while (beri.read((char*)&m_pod, sizeof(m_pod)))
		{
			m_vec.push_back(m_pod); //pošlje podatke v vector 
		}
	}
	
	beri.close();
}

void Datoteka::sortiraj()
{
	std::cout << "sortiram" << std::endl;
	std::ofstream pisi("Highscore.bin", std::ios::binary | std::ios::trunc);

	for (int i = 0; i < m_vec.size(); i++)//sortiranje vectorja 
		for (int j = m_vec.size() - 1; j > i; j--)
			if (m_vec[j - 1].tocke < m_vec[j].tocke)
			{
				struct Podatki t = m_vec[j - 1];
				m_vec[j - 1] = m_vec[j];
				m_vec[j] = t;
			}

	for (int i = 0; i < m_vec.size(); i++)
		pisi.write((char*)&m_vec[i], sizeof(Podatki));//poslje nazaj vector v datoteko

	pisi.close();
	m_vec.clear();//pocisti vector
}

void Datoteka::brisi()
{
	std::ofstream pisi("Temp.bin", std::ios::binary | std::ios::trunc);
	std::ifstream beri("Highscore.bin");
	struct Podatki tmp;
	int t = 0;

	if (beri.is_open())
		while (beri.read((char*)&tmp, sizeof(tmp)))
		{
			if (t < 5)
				pisi.write((char*)&tmp, sizeof(tmp));//5x prebere najboljše rezultate in jih pošlje v temp
			t++;
		}

	pisi.close();
	beri.close();

	remove("Highscore.bin");
	rename("Temp.bin", "Highscore.bin");
}

void Datoteka::izpis()//izpise top 5 rezultatov
{
	std::ifstream beri("Highscore.bin");

	struct Podatki tmp;

	if(beri.is_open())
		while (beri.read((char*)&tmp, sizeof(tmp)))
			std::cout << tmp.ime << " " << tmp.tocke << std::endl;

	beri.close();

	pocistiDat();
}


void Datoteka::replay(int x, int y)
{
	std::ofstream pisi("Replay.bin", std::ios::binary | std::ios::app);

	m_pos.x = x;
	m_pos.y = y;

	pisi.write((char*)&m_pos, sizeof(m_pos));

	pisi.close();
}

void Datoteka::shrani(int playerx, int playery, int lvl, int cas)
{
	std::ofstream pisi("Shranjeno.bin", std::ios::binary | std::ios::trunc);
	std::ofstream pisi1("Lvl.bin", std::ios::binary | std::ios::trunc);

	m_pos.x = playerx;
	m_pos.y = playery;

	m_lvl.lvl = lvl;
	m_lvl.cas = cas;

	pisi.write((char*)&m_pos, sizeof(m_pos));
	pisi1.write((char*)&m_lvl, sizeof(m_lvl));

	pisi.close();
	pisi1.close();
}

bool Datoteka::preveriDatoteke()
{
	std::ifstream dat("Shranjeno.bin");
	std::ifstream dat1("ShraniMap.bin");

	if (dat.peek() == std::ifstream::traits_type::eof())//preverja ce so datoteke prazne
		return 0;
	if (dat1.peek() == std::ifstream::traits_type::eof())
		return 0;

	dat.close();
	dat1.close();

	return 1;
}

int Datoteka::vrniLvl()
{
	int lvl;
	std::ifstream beri("Lvl.bin");

	if (beri.is_open())
		while (beri.read((char*)&lvl, sizeof(lvl)))
			return lvl;

	beri.close();
}

int Datoteka::vrniCas()
{
	int cas;
	std::ifstream beri("Lvl.bin");

	if (beri.is_open())
		while (beri.read((char*)&m_lvl, sizeof(m_lvl)))
			return m_lvl.cas;

	beri.close();
}

Vec2 Datoteka::vrniPos()
{
	std::ifstream beri("Shranjeno.bin");

	if (beri.is_open())
		while (beri.read((char*)&m_pos, sizeof(m_pos)))
			return m_pos;
	beri.close();
}

void Datoteka::pocistiDat()
{
	remove("Lvl.bin");
	remove("Shranjeno.bin");
	remove("ShraniMap.bin");
}

float Datoteka::vrnix(int index)
{
	std::ifstream beri("Shranjeno.bin");
	float tmp;
	
	if (beri.is_open())
	{
		beri.seekg(index * sizeof(m_pos), std::ios::beg);
		beri.read((char*)&m_pos, sizeof(m_pos));
		tmp = m_pos.x;
	}
	beri.close();
	return tmp;
}

float Datoteka::vrniy(int index)
{
	std::ifstream beri("Shranjeno.bin");
	float tmp;

	if (beri.is_open())
	{
		beri.seekg(index * sizeof(m_pos), std::ios::beg);
		beri.read((char*)&m_pos, sizeof(m_pos));
		tmp = m_pos.y;
	}
	beri.close();
	return tmp;
}