#include "TheMathGame.h"



TheMathGame::TheMathGame()
{
	//when game is constructed, 
	//initialize players, equations, timer 
	menuShown = false;
	currentLevel = 0;
	turnsLeft = LEVEL_TURNS;
	finishedLevel = false;
	player1 = NULL;
	player2 = NULL;
	stage = NULL;
	hud = NULL;
}


TheMathGame::~TheMathGame()
{
	// delete all objects
	delete hud;
	if (stage) stage->deleteAll();
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
	else{
		stage->init();
		player1->init();
		player2->init();

	}

	player1->position.set(15, 15);
	player1->getEquation()->position.set(5, 0);
	player1->getLivesObj()->position.set(5, 1);
	player1->getScore()->position.set(10, 1);
	player2->position.set(30, 15);
	player2->getEquation()->position.set(SCREEN_WIDTH - 15, 0);
	player2->getLivesObj()->position.set(SCREEN_WIDTH - 15, 1);
	player2->getScore()->position.set(SCREEN_WIDTH - 10, 1);
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
	gotoxy(15, 0);
	cout << "current level: " << currentLevel;
}


void TheMathGame::doIteration(const list<char>& keyHits)
{
	if (turnsLeft == 0){
		//finishedLevel = true;
		clear_screen();
		gotoxy(30, 15);
		cout << "BOOOO! ! ! ! YOU GUYS SUCK !";
		_getch();
		currentLevel++;
		startLevel(currentLevel);
		return;
	}
	turnsLeft--; 
	//check if one of the keys matches the key set of one of the players
	for (list<char>::const_iterator itr = keyHits.begin(); itr != keyHits.end(); ++itr)
	{
			player1->checkKey(*itr);
			player2->checkKey(*itr);
	}
	
	//move player 1 and 2, if collided, stop
	stage->moveChildren();
	if (player1->answeredRight || player2->answeredRight)
	{
		clear_screen();
		gotoxy(30, 15);
		cout << "WAY TO GO ! ! ! ";
		_getch();
		currentLevel++;
		player1->getEquation()->setLevel(currentLevel);
		player2->getEquation()->setLevel(currentLevel);
		//TODO: addlevelas parameter togenerate level
		player1->getEquation()->generateEquation();
		player2->getEquation()->generateEquation();
		startLevel(currentLevel);
	}
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
	int number = rand() % (currentLevel+10);
	int tries = 10;
	int digits = 1;
	int xPos;
	int yPos;

	while (!placeFound && tries != 0)
	{
		yPos = rand() % (STAGE_HEIGHT);
		xPos = rand() % (SCREEN_WIDTH);
		
		//chek if all neighbors are null
		placeFound = true;

		if (!checkFreeSpace(xPos, yPos)) placeFound = false;

		if (number > 9)
		{
			digits = 2;
			if (!checkFreeSpace((xPos + SCREEN_WIDTH - 1) % SCREEN_WIDTH, yPos)) placeFound = false;
		}
		tries--;
	}

	//if found add a number there
	if (placeFound)
	{
		stage->addChild(new Number(number, 
			(xPos + SCREEN_WIDTH - (digits-1) ) % SCREEN_WIDTH, 
			yPos + HUD_HEIGHT));
	}
}

bool TheMathGame::checkFreeSpace(int xPos, int yPos)
{
	bool freeSpot = true;
	Point centerPoint = Point(xPos, yPos + HUD_HEIGHT);
	Point rightPoint = Point((xPos + 1) % SCREEN_WIDTH, yPos + HUD_HEIGHT);
	Point leftPoint = Point((xPos + SCREEN_WIDTH - 1) % SCREEN_WIDTH, yPos + HUD_HEIGHT);
	Point topPoint = Point(xPos, (yPos + 1) % STAGE_HEIGHT + HUD_HEIGHT);
	Point bottomPoint = Point(xPos, (yPos + (STAGE_HEIGHT)-1) % STAGE_HEIGHT + HUD_HEIGHT);
	
	//change freeSpot=false to return false
	if (stage->getChildAt(centerPoint)) freeSpot = false;
	if (stage->getChildAt(rightPoint)) freeSpot = false;
	if (stage->getChildAt(leftPoint)) freeSpot = false;
	if (stage->getChildAt(topPoint)) freeSpot = false;
	if (stage->getChildAt(bottomPoint)) freeSpot = false;

	//change to return true 
	return freeSpot;
}


void TheMathGame::doSubIteration()
{
	//cout << "sub-Itareation " << endl;
}