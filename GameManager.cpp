//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GameManager.cpp
// ---------------
// GameManager is the top level manager, the game starts from here.
// This class manages the game iterations, menus etc., but WITHOUT knowing anything about the actual game itself.
//
// Author: Amir Kirsh
// First version: 2014-12-09
// 
// This code is part of "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX1, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX1" 
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <list>
#include "GameManager.h"
#include "ISpecificGame.h"
#include "io_utils.h"

using namespace std;

char GameManager::mainMenu()const
{
	// TODO: we may want to improve the menu appearance

	cout << "1. instructions" << endl;
	cout << "2. play game" << endl;
	cout << "3. start from a specific level" << endl;
	cout << "9. exit" << endl;

	char selection = 0;

	do {
		selection = _getch();
	} while(!GameManager::MainMenuOptions::isValidOption(selection));

	return selection;
}

void GameManager::run()
{
	bool userWantsToPlay = true;

	//run till user decides differant
	while(userWantsToPlay) {

		char menuSelection = mainMenu();

		switch(menuSelection)
		{
		case GameManager::MainMenuOptions::PLAY_GAME:

			//set current level to 0  and start playing (will call next to level 1)
			init();
			userWantsToPlay = playGame();

			break;

		case GameManager::MainMenuOptions::PLAY_FROM_SELECTED_SCREEN:

			//get wanted level from user
			cout << "Select a level" << endl;
			int levelSelected ;
			cin >> levelSelected;

			//set the user input as the level before the "current level" and continue
			//this way when calling "next level" it will go to the right one
			currentLevel = levelSelected;
			actualGame.setLevel(currentLevel -1);
			userWantsToPlay = playGame();

			break;

		case GameManager::MainMenuOptions::PRESENT_INSTRUCTIONS:

			//remporary instructions
			//TODO: write normal instructions

			clear_screen();
			cout << "these are the instructions: \nplease play the game...\n\n\n\npress anything to return"<<endl;

			/*char tmp;
			cin >> tmp;
			*/

			_getch();
			clear_screen();

			break;

		case GameManager::MainMenuOptions::EXIT_APPLICATION:

			userWantsToPlay = false;
			break;

		default: // normally we shouldn't get to here...

			userWantsToPlay = false;
		};
	}
}

bool GameManager::playGame()
{
	// we assume that we have multiple levels so there is a need to loop through levels
	// till all levels were played or till user quits - if user quits we do not continue to next level
	//-------------------------------------------------------------
	// this is the game LEVELS loop
	//-------------------------------------------------------------
	char action = GameManager::LevelOptions::NEXT_LEVEL;
	while(actualGame.hasNextLevel() 
		&& action == GameManager::LevelOptions::NEXT_LEVEL) {

		clear_screen();
		action = playNextLevel();
	}
	//-------------------------------------------------------------
	// END of game LEVELS loop
	//-------------------------------------------------------------
	
	// return true if the user wants to keep playing
	return (action != GameManager::LevelOptions::EXIT_APPLICATION);
}

// return action to take in case of ESC
char GameManager::playNextLevel()
{
	//get game level and play the next one
	int gameLevel = actualGame.getLevel();
	currentLevel = gameLevel + 1;
	actualGame.startLevel(currentLevel);
	
	//------------------------------------------------------------------------------
	// here we control the ESC menu
	//------------------------------------------------------------------------------
	bool keepRunning = true;
	char action = 0;

	while(keepRunning)
	{
		//=============================================================================================
		// this is the actual call to play game iterations
		action = doLevelIterations();
		//=============================================================================================
		
		// check action based on game ended (action==BACK_TO_MAIN_MENU) or input from user on ESC menu
		switch(action) 
		{
		case GameManager::LevelOptions::CONTINUE:
			// keepRunning is true, so we only need to set thing right and then - keepRunning!
			//--------------------------------------------------------------------------------
			clear_screen();
			break;

		case GameManager::LevelOptions::REPLAY_LEVEL:
			// keepRunning is true, so we only need to set thing right and then - keepRunning!
			//--------------------------------------------------------------------------------

			//we should concider adding "replayLevel" function to the interface
			actualGame.startLevel(actualGame.getLevel());
			break;

		case GameManager::LevelOptions::BACK_TO_MAIN_MENU:
			//clear screen and reset level before getting back to main menu
			clear_screen();
			actualGame.setLevel(0);
			keepRunning = false;

			break;

		case GameManager::LevelOptions::EXIT_APPLICATION:
			// get out from the loop
			clear_screen();
			keepRunning = false;
			break;

		case GameManager::LevelOptions::NEXT_LEVEL:
			// get out from the loop so we get to the next level
			keepRunning = false;
			break;
		}
		//---------------------------------------
		// END of sub menu action switch
		//---------------------------------------
	}
	//------------------------------------------
	// END of Level keepRunning loop (sub menu)
	//------------------------------------------

	// the actions that may get out from this method are: BACK_TO_MAIN_MENU and EXIT_APPLICATION
	return action;
}

// return action to take in case of ESC
char GameManager::doLevelIterations()
{
	char action;
	bool escapePressed = false;
	//---------------------------------------
	// this is the game iterations loop
	//---------------------------------------
	while(!actualGame.isLevelDone() && !escapePressed) {
		escapePressed = !doIteration();
	}
	//-----------------------------------------------------
	// END of game iterations loop or exit on ESC
	//-----------------------------------------------------

	// check why we are here
	if(actualGame.isLevelDone()) {

		clear_screen();
		gotoxy(30, 15);
		cout  << "WELL DONE" << endl;
		_getch();
		action = GameManager::LevelOptions::NEXT_LEVEL;

	}
	else if (escapePressed) {

		action = 0;
		actualGame.showMenu();
		// TODO: print here the sub menu options to the proper place in screen 
		do {
			action = _getch();
		} while(!GameManager::LevelOptions::isValidOption(action));
	}
	// end of esc pressed
	return action;
}


bool GameManager::doIteration()
{
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle;
	for(unsigned int i=0; i<iterationsPerClockCycle-1; ++i) {
		Sleep(sleepLength);
		actualGame.doSubIteration();
	}
	return doInputIteration();
}

bool GameManager::doInputIteration()
{
	list<char> keyHits(KEYBOARD_HIT_LOOP); // set vector initialize size to the max key strokes that we may collect
	bool shouldContinue = true;
	// get keyboard input in a loop, to get enough keyboard hits
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle / KEYBOARD_HIT_LOOP;
	for(unsigned int i=0; i<KEYBOARD_HIT_LOOP; ++i) {
		Sleep(sleepLength);
		if (_kbhit()) {
			char ch = _getch();
			if(ch == ESC) {
				// ESC pressed
				shouldContinue = false;
			}
			else {
				// we got keyHits byref, so we actually set input into the original list sent here
				keyHits.push_front(ch); // we want recent keys to come first, thus we use push_front
			}
		}
	}
	// send the keystrokes to the game
	// (even if ESC was hit, we may still have something in the keystrokes vector and should use it)
	actualGame.doIteration(keyHits);

	return shouldContinue;
}

