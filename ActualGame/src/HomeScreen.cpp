#include "HomeScreen.h"
#include <iostream>

Homesc::Homesc()
{
	play = new Text(35);
	quit = new Text(35);
	htp = new Text(35);
	naslov = new Text(35);
	lvl = new Text(50);
	congrats = new Text(50);
	go = new Text(50);
	nazaj = new Text(40);

	m_vrsta = 1;
}

void Homesc::draw()
{
	switch (m_vrsta)
	{
	case 1://Home screen
		naslov->drawText(200, 100, "RESI DEZEVNI PRAGOZD", { 231, 116, 39 });
		play->drawText(35, 400, "PLAY", { 255, 255, 255 });
		quit->drawText(666, 515, "QUIT", { 255, 255, 255 });
		htp->drawText(35, 455, "HOW TO PLAY", { 255, 255, 255 });
		break;

	case 3:
		naslov->drawText(280, 100, "HOW TO PLAY", { 231, 116, 39 });//how to play
		nazaj->drawText(350, 515, "Nazaj", { 255, 255, 255 });
		break;

	case 4:
		go->drawText(310, 280, "GAME OVER!", { 255, 255, 255 });//konec igre
		break;

	case 5:
		lvl->drawText(310, 280, "Level 1", { 255, 255, 255 });//lvl1
		break;

	case 6:
		lvl->drawText(310, 280, "Level 2", { 255, 255, 255 });//lvl2
		break;

	case 7:
		lvl->drawText(310, 280, "Level 3", { 255, 255, 255 });//lvl3
		break;

	case 8:
		congrats->drawText(300, 280, "Cestitke!!!", { 255, 255, 255 }); //congrats
		quit->drawText(666, 515, "QUIT", { 255, 255, 255 });
		nazaj->drawText(350, 515, "Nazaj", { 255, 255, 255 });
		break;
	default:
		break;
	}
}

void Homesc::preveri()
{
	if ((Game::event.button.x > 35 && Game::event.button.x < 280) && (Game::event.button.y > 460 && Game::event.button.y < 495))//how to play
		m_vrsta = 3;

	else if ((Game::event.button.x > 350 && Game::event.button.x < 460) && (Game::event.button.y > 525 && Game::event.button.y < 560))//back
		m_vrsta = 1;

	if (m_vrsta == 4)
	{
		if ((Game::event.button.x > 210 && Game::event.button.x < 590) && (Game::event.button.y > 255 && Game::event.button.y < 580))//back to home screen, game over
		{
			getVrsta(1);
		}
	}
	if (m_vrsta == 8)
		if ((Game::event.button.x > 210 && Game::event.button.x < 590) && (Game::event.button.y > 255 && Game::event.button.y < 580))//back to home screen, congrats
			getVrsta(1);
}

Homesc::~Homesc() {}