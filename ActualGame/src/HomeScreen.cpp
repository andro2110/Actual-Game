#include "HomeScreen.h"
#include <iostream>

Homesc::Homesc()
{
	m_homeScreen = TextureManager::LoadTexture("Assets/HomescreenSolid.png");
	m_credits = TextureManager::LoadTexture("Assets/Credits.png");
	m_howToPlay = TextureManager::LoadTexture("Assets/HowToPlay.png");

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.h = 640;
	m_srcRect.w = 800;

	m_destRect.h = 640;
	m_destRect.w = 800;
	m_destRect.x = 0;
	m_destRect.y = 0;
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

	default:
		break;
	}
}

void Homesc::pojdiNazaj()
{
	if (Game::event.type == SDL_MOUSEMOTION && m_vrsta != 1)
		if ((Game::event.button.x > 55 && Game::event.button.x < 175) && (Game::event.button.y > 510 && Game::event.button.y < 540))
			getVrsta(1);
}

Homesc::~Homesc() {}