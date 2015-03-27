#include "TheMathGame.h"



TheMathGame::TheMathGame()
{
	//when game is constructed, 
	//initialize players, equations, timer 
	player1 = new Player('@', "wasd");
	player1->position.set(Point(15, 15));
	player2 = new Player('#', "ijkl");
	player2->position.set(Point(15, 15));
}


TheMathGame::~TheMathGame()
{
	// delete all objects
	delete hud;
	delete stage;
}

void TheMathGame::startLevel()
{
	// init hud and stage objects if null
	if (!hud) hud = new Hud();
	if (!stage) stage = new Stage();
	clear_screen();
}


void TheMathGame::doIteration(const list<char>& keyHits)
{
	for (list<char>::const_iterator itr = keyHits.cbegin();
		itr != keyHits.cend(); ++itr)
	{
		//cout << *itr;
		player1->checkKey(*itr);
		player2->checkKey(*itr);
	}
	if (hud->getRedraw()) hud->render();
	stage->render();
	player1->move();
	player2->move();
	player1->render();
	player2->render();
}
void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}