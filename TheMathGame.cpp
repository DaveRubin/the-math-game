#include "TheMathGame.h"



TheMathGame::TheMathGame()
{
	//when game is constructed, 
	//initialize players, variables 
	menuShown = false;
	finishedLevel = false;
	currentLevel = 0;

	turnsLeft = LEVEL_TURNS;
	player1 = NULL;
	player2 = NULL;
	stage = NULL;
	hud = NULL;
}


TheMathGame::~TheMathGame()
{
	// delete all allocated objects
	if (stage)
	{
		stage->deleteAll();
		delete stage;
	}

	if (hud) delete hud;
	if (player1) delete player1;
	if (player2) delete player2;
	
}
/**
when starting level , initialize stage and players
this function is called both from game manger and TheMathGame
*/
void TheMathGame::startLevel(int levelInput)
{
	finishedLevel = false;
	currentLevel = levelInput;

	// init hud and stage objects if null
	//TODO: we should replace all the  (!object) conditions with boolean for first run
	if (!hud) hud = new Hud();

	if (!stage)
	{
		stage = new Stage();

		//TODO: delete when done
		//test near number
		//stage->getNearestNumberTo(Point(28, 14));
		//_getch();

		//initialize players looks and controls
		player1 = new Player('@', "waxdz");
		player2 = new Player('#', "ijmln");
		yumYums[0] = new NumbersEater(10, 19);
		yumYums[1] = new NumbersEater(70, 19);
	}

	else {
		stage->init();
		player1->init();
		player2->init();
		yumYums[0]->init();
		yumYums[1]->init();
	}

	player1->getEquation()->generateEquation(currentLevel);
	player2->getEquation()->generateEquation(currentLevel);

	//position player on screen
	positionPlayers();

	setColors();

	addPlayersObjectsToStage();

	clear_screen();

	turnsLeft = LEVEL_TURNS;

	gotoxy(30, 0);

	setTextColor(Color::LIGHTGREEN);
	cout << "current level: " << currentLevel;
	setTextColor(DEFAULT_COLOR);
}

void TheMathGame::doIteration(const list<char>& keyHits)
{
	if ( turnsLeft == 0 || 
		(player1->isDead() && player2->isDead()) ) 
	{
		//TODO: create a function for "you guys suck" screen
		//finishedLevel = true;
		clear_screen();
		gotoxy(30, 15);

		setTextColor(Color::LIGHTRED);
		cout << "BOOOO! ! ! ! YOU GUYS SUCK !";
		setTextColor(DEFAULT_COLOR);

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

	//should capsulate to "show screen" method
	if (player1->answeredRight || player2->answeredRight)
	{
		clear_screen();
		gotoxy(30, 15);
		setTextColor(Color::LIGHTGREEN);
		cout << "WAY TO GO ! ! ! ";
		setTextColor(DEFAULT_COLOR);
		_getch();
		currentLevel++;

		//setup for next level
		startLevel(currentLevel);
	}

	//additional actions to be taken in players onIteration
	playersOnIteration();

	//find a place for a new number to be added
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
//	hud->updatePlayerStats(1, player1);
//	hud->updatePlayerStats(2, player2);
	if (hud->getRedraw()) hud->render();
}

void TheMathGame::addNumber()
{
	//find a place
	bool placeFound = false;
	int number = rand() % (currentLevel+9) + 1;
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

		if (!checkFreeSpace(xPos, yPos + HUD_HEIGHT)) placeFound = false;

		if (number > 9)
		{
			digits = 2;
			if (!checkFreeSpace((xPos + SCREEN_WIDTH - 1) % SCREEN_WIDTH, yPos + HUD_HEIGHT)) placeFound = false;
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

/*
position players objects  for each player:
actual player charecter, score ,lives and equation
*/
void TheMathGame::positionPlayers()
{
	//Player1 objects
	player1->position.set(15, 15);
	player1->getEquation()->position.set(5, 0);
	player1->getLivesObj()->position.set(5, 1);
	player1->getScore()->position.set(10, 1);
	player1->getBulletsObj()->position.set(15, 1);

	//Player2 objects
	player2->position.set(30, 15);
	player2->getEquation()->position.set(SCREEN_WIDTH - 25, 0);
	player2->getLivesObj()->position.set(SCREEN_WIDTH - 25, 1);
	player2->getScore()->position.set(SCREEN_WIDTH - 20, 1);
	player2->getBulletsObj()->position.set(SCREEN_WIDTH - 15, 1);

}

//Add players objects (charechter,score,lives and equation) to Stage
void TheMathGame::addPlayersObjectsToStage()
{
	//Player1 objects
	stage->addChild(player1);
	stage->addChild(player1->getScore());
	stage->addChild(player1->getLivesObj());
	stage->addChild(player1->getEquation());
	stage->addChild(player1->getBulletsObj());

	//Player2 objects
	stage->addChild(player2);
	stage->addChild(player2->getScore());
	stage->addChild(player2->getLivesObj());
	stage->addChild(player2->getEquation());
	stage->addChild(player2->getBulletsObj());

	//Add monsters
	stage->addChild(yumYums[0]);
	stage->addChild(yumYums[1]);
}

void TheMathGame::playersOnIteration()
{
	player1->onIteration();
	player2->onIteration();
}

void TheMathGame::setColors()
{
	player1->getLivesObj()->setColor(Color::LIGHTRED);
	player2->getLivesObj()->setColor(Color::LIGHTRED);

	player1->getBulletsObj()->setColor(Color::LIGHTCYAN);
	player2->getBulletsObj()->setColor(Color::LIGHTCYAN);

	player1->getEquation()->setColor(Color::WHITE);
	player2->getEquation()->setColor(Color::WHITE);

	player1->getScore()->setColor(Color::WHITE);
	player2->getScore()->setColor(Color::WHITE);

	player1->setColor(Color::YELLOW);
	player2->setColor(Color::LIGHTMAGENTA);
}

bool TheMathGame::checkFreeSpace(int xPos, int yPos)
{
	bool freeSpot = true;
	Point centerPoint = Point(xPos, yPos );
	Point rightPoint = Point((xPos + 1), yPos );
	Point leftPoint = Point((xPos - 1), yPos );
	Point topPoint = Point(xPos, (yPos + 1) );
	Point bottomPoint = Point(xPos, (yPos-1 )  );

	//warp all points
	centerPoint.warp();
	rightPoint.warp();
	leftPoint.warp();
	topPoint.warp();
	bottomPoint.warp();
	
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
	stage->seconderyMove();
	renderFrame();
//	bullet.move();
//	renderFrame();
}