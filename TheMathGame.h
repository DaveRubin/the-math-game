#ifndef _THEMATHGAME_H_
#define _THEMATHGAME_H_

#pragma once
#include "ISpecificGame.h"
#include "io_utils.h"
#include <iostream>
#include "Stage.h"
#include "DisplayObject.h"
#include "Hud.h"
#include "Player.h"

using namespace std;

/**
TheMathGame class
is the main game controller
it containes all the game parts and syncronize between them all

The game rules are pretty simple at this point:
	two players are moving around the screen
	each player have its own equation to solve and three lives (per level)
	random numbers appear on the screen
	in order to win the level a player needs to "eat" the right solution for his equation 
	eating a wrong solution will cost a pleyr one life
	when players collide, both players will stop moving
**/
class TheMathGame :
	public ISpecificGame
{
	//private members:
	bool menuShown;		//pause game to show menu
	int currentLevel;
	int turnsLeft;
	bool finishedLevel;

	Player *player1;
	Player *player2;
	Stage *stage;
	Hud *hud;
	//move and render objects needed to be rendered
	void renderFrame();
	bool checkFreeSpace(int x, int y);
	void positionPlayers();
	void addPlayersObjectsToStage();

public:
	virtual int getLevel(){ return currentLevel; }
	virtual void setLevel(int levelInput){ currentLevel = levelInput; }
	virtual bool isLevelDone()const{ return finishedLevel; }
	virtual bool hasNextLevel()const{ return currentLevel < 20; }

	virtual void startLevel(int level);
	virtual void doIteration(const list<char>& keyHits);
	virtual void doSubIteration();
	virtual void showMenu();

	TheMathGame();
	~TheMathGame();

	void updateHud(){ hud->setRedraw(); }
	void addNumber();
};


#endif