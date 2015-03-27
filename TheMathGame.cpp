#include "TheMathGame.h"



TheMathGame::TheMathGame()
{
	//when game is constructed, 
	//initialize players, equations, timer 
	actor = new Actor();
	actor->position.set(Point(15, 15));
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
	}
	if (hud->getRedraw()) hud->render();
	stage->render();
	actor->move();
	actor->render();
}
void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}