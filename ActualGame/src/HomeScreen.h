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

	Text* naslov;
	Text* play;
	Text* quit;
	Text* htp;
	Text* lvl;
	Text* congrats;
	Text* go;
	Text* nazaj;


	int m_vrsta;
	int m_framecnt = 0;
};