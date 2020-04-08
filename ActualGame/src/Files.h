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

	~Datoteka() {}

private:
	struct Podatki m_pod;
	std::vector<Podatki> m_vec;
};