#pragma once
#include "ISpecificGame.h"
#include "io_utils.h"
#include <iostream>
#include "Stage.h"
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
	int currentLevel = 0;
	Player *player1 = NULL;
	Player *player2 = NULL;
	//Timer *timer
	Stage *stage  = NULL;
	Hud *hud = NULL;;
public:
	virtual bool isLevelDone()const{return false;}
	virtual bool hasNextLevel()const{return true;}
	virtual void startLevel();
	virtual void doIteration(const list<char>& keyHits);
	virtual void doSubIteration();
	void updateHud(){ hud->setRedraw(); }
	TheMathGame();
	~TheMathGame();
};

