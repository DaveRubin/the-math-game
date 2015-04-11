
#ifndef _STAGE_H_
#define _STAGE_H_

#pragma once
#include "io_utils.h"
#include "Actor.h"
#include <stdlib.h>     
#include <iostream>

using namespace std;


class Stage
{
	DisplayObject **renderList; 
	DisplayObject *matrix[SCREEN_WIDTH][SCREEN_HEIGHT];
	int numChildren = 0;
	int renderListSize = 0;
	void resetMatrix();

public:
	Stage();
	void addChild(DisplayObject*);
	void render();
	void moveChildren();
	void clear();
	DisplayObject *getChildAt(int x, int y);
	void setChildAt(DisplayObject *child,int x, int y);
	void removeChildren(DisplayObject*);
	void init();
};


#endif