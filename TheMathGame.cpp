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
}


void TheMathGame::doIteration(const list<char>& keyHits)
{
	clear_screen();
	hud.render();
	stage.render();
}
void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}