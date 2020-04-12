#pragma once
#include "TextureManager.h"
#include "Besedilo.h"

class Homesc
{
public:
	Homesc();
	~Homesc();

	void getVrsta(int v) { m_vrsta = v; }
	void preveri();
	void draw();

private:

	Text* bes1;
	Text* bes2;
	Text* bes3; 
	Text* bes4;
	Text* bes5;
	Text* konec;
	Text* lvl;
	Text* go;

	int m_vrsta;
	int m_framecnt = 0;
};