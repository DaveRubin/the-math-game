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
	//check if one of the keys matches the key set of one of the players
	for (list<char>::const_iterator itr = keyHits.cbegin();
		itr != keyHits.cend(); ++itr)
	{
		player1->checkKey(*itr);
		player2->checkKey(*itr);
	}
	//move player 1 and 2, if collided, stop
	movePlayers();
	//check if one of them have collected a number
	checkNumbersHit();
	//render all objects needed to be rendered
	renderFrame();
}

void TheMathGame::movePlayers()
{
	player1->move();
	if (player1->collide(*player2)) {
		player1->move(true);
		player1->stop();
	}
	player2->move();
	if (player2->collide(*player1)) {
		player2->move(true);
		player2->stop();
	}

}

void TheMathGame::checkNumbersHit()
{

}

void TheMathGame::renderFrame()
{
	stage->render();
	player1->render();
	player2->render();
	if (hud->getRedraw()) hud->render();
}


void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}