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
	std::ifstream beri("Highscore.bin");

	if (beri.is_open())
	{
		while (beri.read((char*)&m_pod, sizeof(m_pod)))
		{
			m_vec.push_back(m_pod);
		}
	}

	for (auto& i : m_vec)
	{
		std::cout << i.ime << " " << i.tocke << std::endl;
	}
	
	beri.close();
}

void Datoteka::sortiraj()
{
	std::ofstream pisi("Highscore.bin", std::ios::binary | std::ios::trunc);

	for (int i = 0; i < m_vec.size(); i++)//sortiranje
		for (int j = m_vec.size() - 1; j > i; j--)
			if (m_vec[j - 1].tocke < m_vec[j].tocke)
			{
				struct Podatki t = m_vec[j - 1];
				m_vec[j - 1] = m_vec[j];
				m_vec[j] = t;
			}

	for (int i = 0; i < m_vec.size(); i++)
	{
		pisi.write((char*)&m_vec[i], sizeof(Podatki));
	}

	pisi.close();
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
				pisi.write((char*)&tmp, sizeof(tmp));
			t++;
		}

	pisi.close();
	beri.close();
}

void Datoteka::topPet()
{
	std::cout << std::endl;
	std::ifstream beri("Temp.bin");

	struct Podatki tmp;

	if(beri.is_open())
		while (beri.read((char*)&tmp, sizeof(tmp)))
			std::cout << tmp.ime << " " << tmp.tocke << std::endl;

	beri.close();
}

void Datoteka::izpis()
{
	std::cout << std::endl;
	struct Podatki p;
	std::ifstream odpri("Highscore.bin");

	if (odpri.is_open())
		while (odpri.read((char*)&p, sizeof(p)))
			std::cout << p.ime << " " << p.tocke << std::endl;
	odpri.close();
}