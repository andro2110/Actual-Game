#pragma once
#include "TextureManager.h"
#include "Besedilo.h"
#include "Files.h"
#include <string>

class Homesc
{
public:
	Homesc();
	~Homesc();

	void getVrsta(int v) { m_vrsta = v; }
	void preveri();
	void highscore();
	void draw();
	void vpisiIme();

private:

	Text* bes1;
	Text* naslov;
	Text* bes2;
	Text* bes3;
	Text* bes4;
	Text* bes5;

	Datoteka* dat;
	struct Podatki m_pod;
	std::vector<struct Podatki> m_vec;
	std::string s;

	int m_vrsta;
	int m_framecnt = 0;
	bool m_koncano = 0;
};