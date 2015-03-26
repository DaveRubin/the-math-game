#pragma once
#include "io_utils.h"
#include "Point.h"
#include <iostream>
#include <string>

using namespace std;

class DisplayObject
{
	bool visible;
public:
	DisplayObject() :text(""){};;
	Point position;
	void show(){ visible = true; }
	void hide(){ visible = false; }
	bool isVisible(){ return visible; }
	void render();
	string text;
};

