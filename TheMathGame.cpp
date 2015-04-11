#include "TheMathGame.h"



TheMathGame::TheMathGame()
{
	//when game is constructed, 
	//initialize players, equations, timer 
}


TheMathGame::~TheMathGame()
{
	// delete all objects
	delete hud;
	delete stage;
	delete player1;
	delete player2;
}

void TheMathGame::startLevel(int levelInput)
{
	finishedLevel = false;
	currentLevel = levelInput;
	// init hud and stage objects if null
	if (!hud) hud = new Hud();
	if (!stage)
	{
		stage = new Stage();
		player1 = new Player('@', "wasd");

		player2 = new Player('#', "ijkl");

	}

	player1->position.set(15, 15);
	player1->getEquation()->position.set(5, 0);
	player1->getLivesObj()->position.set(5, 1);
	player1->getScore()->position.set(10, 1);
	player2->position.set(30, 15);
	player2->getEquation()->position.set(SCREEN_WIDTH - 15, 0);
	player2->getLivesObj()->position.set(SCREEN_WIDTH - 15, 1);
	player2->getScore()->position.set(SCREEN_WIDTH - 10, 1);
	stage->init();
	stage->addChild(player1);
	stage->addChild(player1->getScore());
	stage->addChild(player1->getLivesObj());
	stage->addChild(player1->getEquation());
	stage->addChild(player2);
	stage->addChild(player2->getScore());
	stage->addChild(player2->getLivesObj());
	stage->addChild(player2->getEquation());

	clear_screen();
	turnsLeft = LEVEL_TURNS;
}


void TheMathGame::doIteration(const list<char>& keyHits)
{
	if (turnsLeft == 0){
		finishedLevel = true;
		return;
	}
	turnsLeft--; 
	//check if one of the keys matches the key set of one of the players
	for (list<char>::const_iterator itr = keyHits.cbegin();
		itr != keyHits.cend(); ++itr)
	{
			player1->checkKey(*itr);
			player2->checkKey(*itr);
	}
	
	//move player 1 and 2, if collided, stop
	stage->moveChildren();
	//render all objects needed to be rendered
	renderFrame();
}

void TheMathGame::showMenu()
{
	/*EXIT_APPLICATION = '1',
		BACK_TO_MAIN_MENU = '2',
		CONTINUE = '3',
		REPLAY_LEVEL = '4',
		NEXT_LEVEL = '5'*/

	stage->clear();
	gotoxy(0, 10);
	cout << "-------------------------------" << endl;
	cout << "1) EXIT_APPLICATION" << endl;
	cout << "2) BACK_TO_MAIN_MENU" << endl;
	cout << "3) CONTINUE" << endl;
	cout << "4) REPLAY_LEVEL" << endl;
	cout << "5) NEXT_LEVEL" << endl;
}

void TheMathGame::renderFrame()
{
	stage->render();
	hud->updatePlayerStats(1, player1);
	hud->updatePlayerStats(2, player2);
	if (hud->getRedraw()) hud->render();
}

void TheMathGame::addNumber()
{
	//find a place
	//if found add a number ther
}


void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}