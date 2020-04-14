#pragma once
#include "TextureManager.h"
#include "Besedilo.h"
#include "Files.h"

class Homesc
{
public:
	Homesc();
	~Homesc();

	void getVrsta(int v) { m_vrsta = v; }
	void preveri();
	//void highscore();
	void draw();

private:

	Text* bes1;
	Text* naslov;
	Text* bes2;
	Text* bes3;
	Text* bes4;
	Text* bes5;

	Datoteka* dat;
	struct Podatki m_pod[5];

	int m_vrsta;
	int m_framecnt = 0;
};