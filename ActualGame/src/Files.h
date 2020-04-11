#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

struct Podatki
{
	char ime[21];
	int tocke;
};

struct Pozicija
{
	int x, y;
};

class Datoteka
{
public:

	Datoteka() {}
	void vpisiPod(int t);
	void preberi();
	void sortiraj();
	void brisi();
	void topPet();
	void izpis();
	void replay(int x, int y);

	~Datoteka() {}

private:
	struct Podatki m_pod;
	std::vector<Podatki> m_vec;
	struct Pozicija m_pos;
};