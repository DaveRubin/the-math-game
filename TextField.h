#pragma once
#include "DisplayObject.h"
#include "io_utils.h"
#include <string>
#include <iostream>

class TextField :
	public DisplayObject
{

	//enum TEXT_DIRECTION {HORIZONTAL , VERTICAL};
	//TEXT_DIRECTION direction;
	string text;
public:
	//\x06\x05\x04\x03\x02\x01
	TextField() :text(""){};
	TextField(string s) :text(s){};
	TextField(TextField &tf) :text(tf.text){};

	void setText(string s);
	string getText(){ return text; }
	virtual void render();
	void clear();
};

