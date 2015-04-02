#ifndef _HUD_H_
#define _HUD_H_

#pragma once
#include "io_utils.h"
#include "Equation.h"
#include "LivesMeter.h"
#include "TextField.h"
#include <stdlib.h>     
#include <iostream>

class Hud
{
	Equation *equation1;
	Equation *equation2;
	TextField *score1;
	TextField *score2;
	LivesMeter *lives1;
	LivesMeter *lives2;
	TextField *seperator;

	bool redraw = true;
	void createNewObjects();
public:
	Hud();
	void render();
	void setRedraw(){ redraw = true; }
	bool getRedraw(){ return redraw; }
};


#endif