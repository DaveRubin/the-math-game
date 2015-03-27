#include "TheMathGame.h"



TheMathGame::TheMathGame()
{
	//when game is constructed, 
	//initialize players, equations, timer 
}


TheMathGame::~TheMathGame()
{
	// delete all objects
}

void TheMathGame::startLevel()
{
	//cout << "yo yo " << endl;
	clear_screen();
}


void TheMathGame::doIteration(const list<char>& keyHits)
{
	hud.render();

	stage.render();
	for (list<char>::const_iterator itr = keyHits.cbegin();
		itr != keyHits.cend(); ++itr)
	{
		//cout << *itr;
	}
}
void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}