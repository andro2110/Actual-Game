#pragma once
#include "Vec2D.h"
#include "TextureManager.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>

class Predmet
{
protected:
	Vec2 m_position;
	Vec2 m_smer;

	int m_speed = 3;
	int m_framecount;

	SDL_Texture* m_texture;
	SDL_Rect m_srcRect, m_destRect;
	float m_scale;

public:
	Predmet(const char* path, float scale);
	virtual ~Predmet();

	virtual void update();
	void premik();
	virtual void border();
	virtual void posUpdate();
	int getx() { return m_position.x; }
	int gety() { return m_position.y; }
	void render();
};

class Igralec : public Predmet
{
private:

public:
	Igralec(const char* path, float scale);
	~Igralec();

	void update() override;
	void posUpdate() override;
};

class Hudoba : public Predmet
{
private:
	int m_randx;
	int m_randy;
	bool m_pravoMesto;

public:
	Hudoba(const char* path, float scale);
	~Hudoba();

	void update() override;
	void changePos();
	void posUpdate() override;
	void preveriPos();
	bool pravoMesto() { return m_pravoMesto; }

	int randx() { return m_randx; }
	int randy() { return m_randy; }
};

class Staroselec : public Predmet
{
private:
	//Hudoba m_hudoba;

public:
	Staroselec(const char* path, float scale);
	~Staroselec();

	void update() override;
	void posUpdate() override;
	//void getHudoba(std::vector<Hudoba>::iterator it) { m_hudoba = *(it); }
	void changePos(int x, int y);
};