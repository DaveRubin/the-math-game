#include "TheMathGame.h"



TheMathGame::TheMathGame()
{
	//when game is constructed, 
	//initialize players, equations, timer 
	//cout << "Itareation " <<  endl;
	Equation *a = new Equation();
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
	cout << "Itareation " <<  endl;
}
void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}