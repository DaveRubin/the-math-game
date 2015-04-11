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
	addNumber();
	//render all objects needed to be rendered
	renderFrame();
}

void TheMathGame::showMenu()
{
	stage->clear();
	gotoxy(0, 10);

	string lineString = "";
	lineString.append(24, '\xB2');

	cout << "			" << '\xB2' << lineString << endl;
	cout << "			" << '\xB2' << " 1) EXIT_APPLICATION	" << '\xB2' << endl;
	cout << "			" << '\xB2' << " 2) BACK_TO_MAIN_MENU	" << '\xB2' << endl;
	cout << "			" << '\xB2' << " 3) CONTINUE		" << '\xB2' << endl;
	cout << "			" << '\xB2' << " 4) REPLAY_LEVEL	" << '\xB2' << endl;
	cout << "			" << '\xB2' << " 5) NEXT_LEVEL		" << '\xB2' << endl;
	cout << "			" << '\xB2' << lineString << endl;
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
	bool placeFound = false;
	int number = rand() % currentLevel;
	int tries = 10;
	int xPos;
	int yPos;
	while (!placeFound && tries != 0)
	{
		yPos = rand() % (SCREEN_HEIGHT - HUD_HEIGHT);
		xPos = rand() % (SCREEN_WIDTH);
		//chek if all neighbors are null
		placeFound = true;
		if (stage->getChildAt(yPos + HUD_HEIGHT, xPos)) placeFound = false;
		if (stage->getChildAt(yPos + HUD_HEIGHT, (xPos + 1) % SCREEN_WIDTH)) placeFound = false;
		if (stage->getChildAt(yPos + HUD_HEIGHT, (xPos + SCREEN_WIDTH - 1) % SCREEN_WIDTH)) placeFound = false;
		if (stage->getChildAt((yPos + 1) % HUD_HEIGHT + HUD_HEIGHT, xPos)) placeFound = false;
		if (stage->getChildAt((yPos + (SCREEN_HEIGHT - HUD_HEIGHT) - 1) % HUD_HEIGHT + HUD_HEIGHT, xPos)) placeFound = false;
		tries--;
	}
	//if found add a number there
	if (placeFound){
		stage->addChild(new Number(number, xPos, yPos));
	}
}


void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}