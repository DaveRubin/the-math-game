#pragma once
#include "DisplayObject.h"
#include "io_utils.h"
#include <string>
#include <iostream>

class TextField :
	public DisplayObject
{

	enum TEXT_DIRECTION {HORIZONTAL , VERTICAL};
	TEXT_DIRECTION direction;

public:
	//\x06\x05\x04\x03\x02\x01
	TextField(){};
	TextField(string s){ text = s; };
	void setText(string s){ text = s; };
};

