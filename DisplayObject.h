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
	~DisplayObject();
	Point position;
	void show();
	void hide();
	bool isVisible();
	void render();
	string text;
};

