#include "HomeScreen.h"
#include <iostream>

Homesc::Homesc()
{
	bes1 = new Text(35);
	naslov = new Text(50);
	bes2 = new Text(35);
	bes3 = new Text(35);
	bes4 = new Text(35);
	bes5 = new Text(35);

	m_vrsta = 1;
}

void Homesc::draw()
{
	switch (m_vrsta)
	{
	case 1://Home screen
		naslov->drawText(100, 100, "RESI DEZEVNI PRAGOZD", { 231, 116, 39 });
		bes1->drawText(35, 350, "PLAY", { 255, 255, 255 });
		bes5->drawText(35, 400, "HIGHSCORES", { 255, 255, 255 });
		bes2->drawText(666, 515, "QUIT", { 255, 255, 255 });
		bes3->drawText(35, 455, "HOW TO PLAY", { 255, 255, 255 });
		bes4->drawText(35, 515, "REPLAY", { 255, 255, 255 });
		break;

	case 2:
		naslov->drawText(280, 100, "HOW TO PLAY", { 231, 116, 39 });//how to play
		bes1->drawText(350, 515, "Back", { 255, 255, 255 });
		bes2->drawText(35, 150, "Prepreci pozar... lahko gasis in sadis", { 255, 255, 255 });
		bes3->drawText(35, 200, "Unici hudobe (vitezi), buce ti pomagajo", {255, 255, 255});
		bes4->drawText(35, 250, "Premikas se z A, W, S, D", { 255, 255, 255 });
		bes5->drawText(35, 300, "Pavza -> p", { 255, 255, 255 });
		bes1->drawText(35, 350, "2 sekundi na unicenem drevesu = novo drevo", { 255, 255, 255 });
		break;

	case 3:
		naslov->drawText(300, 280, "GAME OVER!", { 255, 255, 255 });//konec igre
		bes1->drawText(666, 515, "QUIT", { 255, 255, 255 });
		bes2->drawText(350, 515, "Back", { 255, 255, 255 });
		bes3->drawText(254, 340, "Klikni na konzolo in vpisi ime", { 255, 255, 255 });
		break;

	case 4:
		naslov->drawText(310, 280, "Level 1", { 255, 255, 255 });//lvl1
		break;

	case 5:
		naslov->drawText(310, 280, "Level 2", { 255, 255, 255 });//lvl2
		break;

	case 6:
		naslov->drawText(310, 280, "Level 3", { 255, 255, 255 });//lvl3
		break;

	case 7:
		naslov->drawText(200, 150, "Cestitke!!!", { 255, 255, 255 }); //congrats
		bes1->drawText(666, 515, "QUIT", { 255, 255, 255 });
		bes2->drawText(350, 515, "Back", { 255, 255, 255 });
		break;

	case 8:
		naslov->shadedText(305, 230, "Pause", { 255, 255, 255, 255 }, { 0, 0, 0, 255 });//pavza
		bes1->shadedText(666, 515, "Quit", { 255, 255, 255, 255 }, { 0, 0, 0, 255 });
		bes2->shadedText(280, 400, "Save & quit", { 255, 255, 255, 255 }, { 0, 0, 0, 255 });
		break;

	case 9:
		naslov->drawText(270, 230, "Se v delu :/", { 255, 255, 255, 255 });//replay
		bes1->drawText(350, 515, "Back", { 255, 255, 255 });
		break;

	case 10:
		naslov->drawText(230, 150, "Cestitke!!!", { 255, 255, 255 }); //congrats
		bes1->drawText(666, 515, "QUIT", { 255, 255, 255 });
		bes2->drawText(350, 515, "Back", { 255, 255, 255 });
		bes3->drawText(100, 280, "Vpisi ime", { 255, 255, 255 });

		if (m_koncano == false)
		{
			vpisiIme();
			izpisiText();
		}
		izpisiText();
		break;

	case 11://highscore
		naslov->drawText(250, 100, "Highscores", { 255, 255, 255 });
		bes1->drawText(350, 515, "Back", { 255, 255, 255 });

		highscore();
		break;
	default:
		break;
	}
}

void Homesc::preveri()
{
	switch (m_vrsta)
	{
	case 1:	
		if ((Game::event.button.x > 35 && Game::event.button.x < 280) && (Game::event.button.y > 460 && Game::event.button.y < 495))//how to play
			m_vrsta = 2;
		if ((Game::event.button.x > 35) && (Game::event.button.x < 270) && (Game::event.button.y > 415) && (Game::event.button.y < 440))//highscore
			m_vrsta = 11;
		break;

	case 2: //how to play
		
	case 9://replay

	case 10://congrats

	case 11://highscore

		if ((Game::event.button.x > 350 && Game::event.button.x < 460) && (Game::event.button.y > 525 && Game::event.button.y < 560))//back
			m_vrsta = 1;
		break;

	case 3:
		break;
	default:
		break;
	}

	//if ((Game::event.button.x > 350 && Game::event.button.x < 460) && (Game::event.button.y > 525 && Game::event.button.y < 560))//back to home screen, game over
	//if ((Game::event.button.x > 210 && Game::event.button.x < 590) && (Game::event.button.y > 255 && Game::event.button.y < 580))//back to home screen, congrats
}

void Homesc::highscore()
{
	std::ifstream beri("Highscore.bin");
	int ypos = 180;
	std::string tmpstr;

	if (beri.is_open())
		while (beri.read((char*)&m_pod, sizeof(m_pod)))
			m_vec.push_back(m_pod);

	beri.close();

	for (int i = 0; i < m_vec.size(); i++)
	{
		tmpstr = std::to_string(m_vec[i].tocke);
		bes2->drawText(200, ypos, m_vec[i].ime, { 255, 255, 255 });
		bes1->drawText(200 + bes2->vrniRect().w + (bes2->vrniRect().w / 2) , ypos, tmpstr, { 255, 255 ,255 });
		ypos += 50;
	}
	m_vec.clear();
}

void Homesc::vpisiIme()
{
	switch (Game::event.type)
	{
	case SDL_KEYDOWN:
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_a:
			s.push_back('a');
			break;
		case SDLK_b:
			s.push_back('b');
			break;
		case SDLK_c:
			s.push_back('c');
			break;
		case SDLK_d:
			s.push_back('d');
			break;
		case SDLK_e:
			s.push_back('e');
			break;
		case SDLK_f:
			s.push_back('f');
			break;
		case SDLK_g:
			s.push_back('g');
			break;
		case SDLK_h:
			s.push_back('h');
			break;
		case SDLK_i:
			s.push_back('i');
			break;
		case SDLK_j:
			s.push_back('j');
			break;
		case SDLK_k:
			s.push_back('k');
			break;
		case SDLK_l:
			s.push_back('l');
			break;
		case SDLK_m:
			s.push_back('m');
			break;
		case SDLK_n:
			s.push_back('n');
			break;
		case SDLK_o:
			s.push_back('o');
			break;
		case SDLK_p:
			s.push_back('p');
			break;
		case SDLK_r:
			s.push_back('r');
			break;
		case SDLK_s:
			s.push_back('s');
			break;
		case SDLK_t:
			s.push_back('t');
			break;
		case SDLK_u:
			s.push_back('u');
			break;
		case SDLK_v:
			s.push_back('v');
			break;
		case SDLK_z:
			s.push_back('z');
			break;
		case SDLK_q:
			s.push_back('q');
			break;
		case SDLK_w:
			s.push_back('w');
			break;
		case SDLK_y:
			s.push_back('y');
			break;
		case SDLK_x:
			s.push_back('x');
			break;
		case SDLK_SPACE:
			s.push_back(' ');
			break;
		case SDLK_BACKSPACE:
			stej++;
			if (stej == m_timer && s.size() > 0)//da ne spammas backspacea k ti drgac jau error
			{
				s.erase(s.end() - 1);
				stej = 0;
			}
			break;
		case SDLK_KP_ENTER:
			m_koncano = 1;
			break;

		default:
			break;
		}

	default:
		break;
	}

	if (s.size() > 20)//max dolzina je 20
		s.erase(s.end() - 1);
}

void Homesc::izpisiText()
{
	bes1->drawText(350, 280, s, { 255, 255, 255 });
}

Homesc::~Homesc() {}