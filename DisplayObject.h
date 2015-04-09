
#ifndef _DISPLAYOBJECT_H_
#define _DISPLAYOBJECT_H_

#pragma once
#include "io_utils.h"
#include "Point.h"
#include <iostream>
#include <string>

using namespace std;
class Stage;


class DisplayObject
{
	Stage *stage;
	bool visible;
	bool redraw;
	bool staticObj;
	string objectType = "DisplayObject";

public:
	Point position;

	DisplayObject() :visible(true), redraw(true), staticObj(true){};

	void show(){ visible = true; }
	void hide(){ visible = false; }
	bool isVisible(){ return visible; }
	void setRedraw( bool val ){ redraw = val; }
	bool getRedraw(){ return redraw; }

	bool isStatic(){ return staticObj; }
	void setStatic(bool val){ staticObj = val; }

	void setType(string s) { objectType = s; }
	string getType(){ return objectType; }

	void setStage(Stage *stageP){ stage = stageP; }
	Stage *getStage(){ return stage; }

	virtual void render(){};
	virtual void clear(){};
};

#endif