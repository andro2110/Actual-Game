#pragma once
#include "Vec2D.h"
#include "TextureManager.h"
#include <cstdlib>
#include <iostream>
#include <math.h>

class Predmet
{
protected:
	Vec2 m_position;
	Vec2 m_smer;

	int m_speed = 3;

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
	//bool collisonDetection(Hudoba* a[10]);
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

public:
	Hudoba(const char* path, float scale);
	~Hudoba();

	void update() override;
	int getx() { return m_position.x; }
	int gety() { return m_position.y; }
	void posUpdate() override;

};
