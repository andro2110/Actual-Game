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

struct Lvl
{
	int lvl, cas;
};

class Datoteka
{
public:

	Datoteka() {}
	void vpisiPod(int tocke, std::string ime);//highscore//
	void preberi();
	void sortiraj();
	void brisi();
	void izpis();
	void replay(int x, int y);//replay//
	void shrani(int playerx, int playery, int lvl, int cas);//save & quit//
	bool preveriDatoteke();//preveri ali so datoteke prazne
	int vrniLvl();
	int vrniCas();
	Vec2 vrniPos();
	void pocistiDat();//pobrise datoteke
	float vrnix(int index);
	float vrniy(int index);

	~Datoteka() {}

private:
	struct Podatki m_pod;
	std::vector<Podatki> m_vec;
	Vec2 m_pos;
	struct Lvl m_lvl;
};