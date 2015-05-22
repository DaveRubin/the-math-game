
#ifndef _DISPLAYOBJECT_H_
#define _DISPLAYOBJECT_H_

#pragma once
#include "io_utils.h"
#include "Point.h"
#include "Color.h"
#include <iostream>
#include <string>

using namespace std;
class Stage;

//TODO: create virtual destructor!
class DisplayObject
{
	Color printColor;
	Stage *stage;
	//fast objects will get secondary motion
	bool isFast;
	//only visible objects will be rendered
	bool visible;
	bool redraw;
	//static object will not be ask to move
	bool staticObj;
	//string declaring object type
	string objectType;

public:
	Point position;

	DisplayObject():isFast(false), visible(true), redraw(true), staticObj(true), objectType("DisplayObject"){};

	void setColor(Color newColor) { printColor = newColor; }
	Color getColor() { return printColor; }

	//isFast getter setter
	void setFast(bool val) { isFast = val; }
	bool isFastObject() { return isFast; }

	//visible getter/setter
	void show(){ visible = true; }
	void hide(){ visible = false; }
	bool isVisible(){ return visible; }

	//redraw getter setter
	void setRedraw( bool val ){ redraw = val; }
	bool getRedraw(){ return redraw; }

	//static getter setter
	bool isStatic(){ return staticObj; }
	void setStatic(bool val){ staticObj = val; }

	//objectType getter setter
	void setType(string s) { objectType = s; }
	string getType(){ return objectType; }

	//stage getter setter
	void setStage(Stage *stageP){ stage = stageP; }
	Stage *getStage(){ return stage; }

	//interface functions
	virtual void render(){};
	virtual void clear(){};
	virtual void kill(){};					
	virtual int getWidth(){ return 1; };	//will get the width of the display content 
};

#endif