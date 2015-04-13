#ifndef _HUD_H_
#define _HUD_H_

#pragma once
#include "io_utils.h"
#include "Equation.h"
#include "LivesMeter.h"
#include "TextField.h"
#include "Player.h"
#include <stdlib.h>     
#include <iostream>

class Hud
{
	//TODO: get rid f hud, and set the seperator in the main game
	TextField *seperator;

	bool redraw;
	void createNewObjects();
public:
	Hud() ;
	void render();
	void setRedraw(){ redraw = true; }
	bool getRedraw(){ return redraw; }
	void updatePlayerStats(int playerNum, Player *player);
};


#endif