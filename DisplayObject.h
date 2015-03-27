#pragma once
#include "io_utils.h"
#include "Point.h"
#include <iostream>
#include <string>

using namespace std;

class DisplayObject
{
	bool visible;
	bool redraw;
public:
	DisplayObject() :visible(true), redraw(true){};
	Point position;
	void show(){ visible = true; }
	void hide(){ visible = false; }
	bool isVisible(){ return visible; }
	void setRedraw(bool val){ redraw = val; }
	bool getRedraw(){ return redraw; }

	virtual void render(){};
};

