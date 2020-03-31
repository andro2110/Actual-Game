#pragma once
#include "Vec2D.h"
#include "TextureManager.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>
#include <memory>

class Predmet
{
protected:
	Vec2 m_position;
	Vec2 m_smer;

	int m_speed;
	int m_framecount;

	SDL_Texture* m_texture;
	SDL_Rect m_srcRect, m_destRect;
	float m_scale;

public:
	Predmet(const char* path, float scale);
	virtual ~Predmet();

	virtual void update();
	virtual void border();
	virtual void posUpdate();
	int getx() { return m_position.x; }
	int gety() { return m_position.y; }
	//void premik();
	void render();
	bool checkCollision(SDL_Rect dest, SDL_Rect src);
	void setTex(const char* path) { m_texture = TextureManager::LoadTexture(path); }

	SDL_Rect vrniSrc() { return m_srcRect; }
	SDL_Rect vrniDest() { return m_destRect; }
};

class Igralec : public Predmet
{
private:
	int m_zamik = 0;
public:
	Igralec(const char* path, float scale);
	~Igralec();

	void update() override;
	void premik();
	void posUpdate() override;
};

class Hudoba : public Predmet
{
private:
	int m_randx;
	int m_randy;
	bool m_pravoMesto;
	int m_lvl = 1;
	int m_zamik;

public:
	Hudoba(const char* path, float scale, int lvl);
	~Hudoba();

	void update() override;
	void premakni();
	void posUpdate() override;
	void preveriPos();
	bool pravoMesto() { return m_pravoMesto; }
	void nextLvl(int lvl) { m_lvl = lvl; };
};

class Staroselec : public Predmet
{
private:

	int m_nasMestox;
	int m_nasMestoy;
	bool m_pravoMesto;

	bool m_zasedenost = 0;
	int m_zamik;

	int m_life = 3;

public:
	Staroselec(const char* path, float scale);
	~Staroselec();

	void update() override;
	void posUpdate() override;
	void getHudoba(int x, int y);
	void premakni();
	void preveriPos();
	void changePos(int x, int y);
	void slediHudobi(std::vector<std::unique_ptr<Hudoba>>& a);

	bool pravoMesto() { return m_pravoMesto; }
	bool zasedenost() { return m_zasedenost; }
	void getZasedenost(bool x) { m_zasedenost = x; }
	int getLife() { return m_life; }
};