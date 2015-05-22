
#ifndef _STAGE_H_
#define _STAGE_H_

#include "io_utils.h"
#include "Actor.h"
#include <stdlib.h>     
#include <iostream>

using namespace std;


class Stage
{
	DisplayObject **renderList; 
	DisplayObject *matrix[SCREEN_WIDTH][SCREEN_HEIGHT];
	int numChildren;
	int renderListSize;
	void resetMatrix();

public:
	Stage();
	void addChild(DisplayObject*);
	void render();
	void moveChildren();
	void seconderyMove();
	void clear();

	DisplayObject *getChildAt(int x, int y);
	DisplayObject *getChildAt(Point p);

	Point *getNearestNumberTo(Point position);

	void setChildAt(DisplayObject *child,int x, int y);
	void removeChildren(DisplayObject*);
	void init();
	void deleteAll();
};


#endif