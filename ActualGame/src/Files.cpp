#include "Files.h"

void Datoteka::vpisiPod(int tocke)
{
	std::ofstream pisi("Highscore.bin", std::ios::binary | std::ios::app);

	std::cout << "Vnesi ime:";
	gets_s(m_pod.ime);
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
			m_vec.push_back(m_pod); //po�lje podatke v vector 
		}
	}
	
	beri.close();
}

void Datoteka::sortiraj()
{
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
				pisi.write((char*)&tmp, sizeof(tmp));//5x prebere najbolj�e rezultate in jih po�lje v temp
			t++;
		}

	//Remove("Highscore.bin");
	//rename("Temp.bin", "Highscore.bin");

	pisi.close();
	beri.close();
}

void Datoteka::topPet()//izpise top 5 rezultatov
{
	std::ifstream beri("Temp.bin");

	struct Podatki tmp;

	if(beri.is_open())
		while (beri.read((char*)&tmp, sizeof(tmp)))
			std::cout << tmp.ime << " " << tmp.tocke << std::endl;

	beri.close();
}

void Datoteka::izpis()
{
	std::ifstream beri("Shranjeno.bin");
	Vec2 p;

	if (beri.is_open())
		while (beri.read((char*)&p, sizeof(p)))
			std::cout << p.x << " " << p.y << std::endl;
	beri.close();
}

void Datoteka::replay(int x, int y)
{
	std::ofstream pisi("Replay.bin", std::ios::binary | std::ios::app);

	m_pos.x = x;
	m_pos.y = y;

	pisi.write((char*)&m_pos, sizeof(m_pos));

	pisi.close();
}

void Datoteka::shrani(int playerx, int playery, int lvl)
{
	std::ofstream pisi("Shranjeno.bin", std::ios::binary | std::ios::trunc);
	std::ofstream pisi1("Lvl.bin", std::ios::binary | std::ios::trunc);

	m_pos.x = playerx;
	m_pos.y = playery;

	pisi.write((char*)&m_pos, sizeof(m_pos));
	pisi1.write((char*)&lvl, sizeof(lvl));

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

Vec2 Datoteka::vrniPos()
{
	std::ifstream beri("Shranjeno.bin");

	if (beri.is_open())
		while (beri.read((char*)&m_pos, sizeof(m_pos)))
			return m_pos;
	beri.close();
}