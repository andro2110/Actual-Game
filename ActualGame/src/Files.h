#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include "Vec2D.h"

struct Podatki//highscore
{
	char ime[21];
	int tocke;
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
	bool preveriDatoteke();//preveri ali so datoteke prazne
	int vrniLvl();
	Vec2 vrniPos();
	void pocistiDat();//pobrise datoteke
	float vrnix(int index);
	float vrniy(int index);

	~Datoteka() {}

private:
	struct Podatki m_pod;
	std::vector<Podatki> m_vec;
	Vec2 m_pos;
};