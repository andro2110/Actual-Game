#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

struct Podatki//highscore
{
	char ime[21];
	int tocke;
};

struct Pozicija//replay
{
	int x, y;
};

struct Shrani
{
	int x, y, lvl;// tab[10][16], uniceno, tocke;
};

struct shraniMap
{
	int tab[10][16], uniceno, tocke;
};

class Datoteka
{
public:

	Datoteka() {}
	void vpisiPod(int t);//highscore//
	void preberi();
	void sortiraj();
	void brisi();
	void topPet();//highscore//
	void izpis();
	void replay(int x, int y);//replay//
	void shrani(int playerx, int playery, int lvl);//save & quit//

	~Datoteka() {}

private:
	struct Podatki m_pod;
	std::vector<Podatki> m_vec;
	struct Pozicija m_pos;
	struct Shrani m_shrani;
};