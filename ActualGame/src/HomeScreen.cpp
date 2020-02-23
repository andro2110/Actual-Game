#include "HomeScreen.h"
#include <iostream>

Homesc::Homesc()
{
	m_homeScreen = TextureManager::LoadTexture("Assets/HomescreenSolid.png");
	m_credits = TextureManager::LoadTexture("Assets/Credits.png");
	m_howToPlay = TextureManager::LoadTexture("Assets/HowToPlay.png");
	m_gameOver = TextureManager::LoadTexture("Assets/GameOver.png");
	m_lvl1 = TextureManager::LoadTexture("Assets/lvl1.png");
	m_lvl2 = TextureManager::LoadTexture("Assets/lvl2.png");
	m_lvl3 = TextureManager::LoadTexture("Assets/lvl3.png");
	m_congrats = TextureManager::LoadTexture("Assets/Congrats.png");

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.h = 640;
	m_srcRect.w = 800;

	m_destRect.h = 640;
	m_destRect.w = 800;
	m_destRect.x = 0;
	m_destRect.y = 0;

	m_vrsta = 1;
}

void Homesc::draw()
{
	switch (m_vrsta)
	{
	case 1:
		TextureManager::Draw(m_homeScreen, m_srcRect, m_destRect);//navadni homescreen
		break;

	case 2:
		TextureManager::Draw(m_credits, m_srcRect, m_destRect);//credits
		break;

	case 3:
		TextureManager::Draw(m_howToPlay, m_srcRect, m_destRect);//how to play
		break;

	case 4:
		TextureManager::Draw(m_gameOver, m_srcRect, m_destRect);//game over
		break;

	case 5:
		TextureManager::Draw(m_lvl1, m_srcRect, m_srcRect);//lvl1 slika
		break;

	case 6:
		TextureManager::Draw(m_lvl2, m_srcRect, m_destRect);//lvl2
		break;

	case 7:
		TextureManager::Draw(m_lvl3, m_srcRect, m_destRect);//lvl3
		break;

	case 8:
		TextureManager::Draw(m_congrats, m_srcRect, m_destRect);//congrats

	default:
		break;
	}
}

void Homesc::preveri()
{

	if ((Game::event.button.x > 35 && Game::event.button.x < 455) && (Game::event.button.y > 455 && Game::event.button.y < 485))//credits
		m_vrsta = 2;

	else if ((Game::event.button.x > 35 && Game::event.button.x < 235) && (Game::event.button.y > 515 && Game::event.button.y < 545))//how to play
		m_vrsta = 3;

	else if ((Game::event.button.x > 340 && Game::event.button.x < 455) && (Game::event.button.y > 555 && Game::event.button.y < 580))//back
		m_vrsta = 1;

	if (m_vrsta == 4)
	{
		if ((Game::event.button.x > 210 && Game::event.button.x < 590) && (Game::event.button.y > 255 && Game::event.button.y < 580))//back to home screen, game over
		{
			getVrsta(1);
		}
	}
}

Homesc::~Homesc() {}