#include "TheMathGame.h"



TheMathGame::TheMathGame()
{
	//when game is constructed, 
	//initialize players, equations, timer 
	Equation *a = new Equation();
	DisplayObject *d = new DisplayObject();
	t = new TextField();


	a->position.set(5, 5);
	d->position.set(5, 6);
	t->position.set(5, 7);
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
	t->render();
}
void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}