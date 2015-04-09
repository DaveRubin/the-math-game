
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
	int numChildren = 0;
	int renderListSize = 0;

public:

	void addChild(DisplayObject*);
	void render();
	void moveChildren();
	void clear();
};


#endif