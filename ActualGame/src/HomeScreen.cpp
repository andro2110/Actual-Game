#include "HomeScreen.h"
#include <iostream>

Homesc::Homesc()
{
	bes1 = new Text(35);
	bes2 = new Text(35);
	bes3 = new Text(35);
	bes4 = new Text(35);
	lvl = new Text(50);
	konec = new Text(50);
	go = new Text(50);

	m_vrsta = 1;
}

void Homesc::draw()
{
	switch (m_vrsta)
	{
	case 1://Home screen
		bes1->drawText(200, 100, "RESI DEZEVNI PRAGOZD", { 231, 116, 39 });
		bes2->drawText(35, 400, "PLAY", { 255, 255, 255 });
		bes3->drawText(666, 515, "QUIT", { 255, 255, 255 });
		bes4->drawText(35, 455, "HOW TO PLAY", { 255, 255, 255 });
		break;

	case 3:
		bes1->drawText(280, 100, "HOW TO PLAY", { 231, 116, 39 });//how to play
		bes1->drawText(350, 515, "Back", { 255, 255, 255 });
		break;

	case 4:
		konec->drawText(300, 280, "GAME OVER!", { 255, 255, 255 });//konec igre
		bes2->drawText(666, 515, "QUIT", { 255, 255, 255 });
		bes1->drawText(350, 515, "Back", { 255, 255, 255 });
		bes3->drawText(254, 340, "Klikni na konzolo in vpiši ime", { 255, 255, 255 });
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
		konec->drawText(300, 250, "Cestitke!!!", { 255, 255, 255 }); //congrats
		bes2->drawText(666, 515, "QUIT", { 255, 255, 255 });
		bes1->drawText(350, 515, "Back", { 255, 255, 255 });
		bes3->drawText(254, 340, "Klikni na konzolo in vpisi ime", { 255, 255, 255 });
		break;

	case 9:
		konec->shadedText(305, 230, "Pause", { 255, 255, 255, 255 }, { 0, 0, 0, 255 });//pavza
		bes1->shadedText(666, 515, "Quit", { 255, 255, 255, 255 }, { 0, 0, 0, 255 });
		bes2->shadedText(280, 400, "Save & quit", { 255, 255, 255, 255 }, { 0, 0, 0, 255 });
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

	else if (m_vrsta == 4)
	{
		if ((Game::event.button.x > 350 && Game::event.button.x < 460) && (Game::event.button.y > 525 && Game::event.button.y < 560))//back to home screen, game over
		{
			getVrsta(1);
		}
	}
	else if (m_vrsta == 8)
	{
		if ((Game::event.button.x > 210 && Game::event.button.x < 590) && (Game::event.button.y > 255 && Game::event.button.y < 580))//back to home screen, congrats
			getVrsta(1);
	}
}

Homesc::~Homesc() {}