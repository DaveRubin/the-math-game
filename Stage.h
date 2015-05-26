
#ifndef _STAGE_H_
#define _STAGE_H_

#include "io_utils.h"
#include "Actor.h"
#include <stdlib.h>     
#include <iostream>
#include <list>

using namespace std;


class Stage
{
	DisplayObject *matrix[SCREEN_WIDTH][SCREEN_HEIGHT];
	list<DisplayObject*> renderList;
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

	DisplayObject *getNearestNumberTo(Point position);

	void setChildAt(DisplayObject *child,int x, int y);
	void removeChildren(DisplayObject*);
	void init();
	void deleteAll();
};


#endif