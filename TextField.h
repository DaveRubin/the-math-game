#ifndef _TEXTFIELD_H_
#define _TEXTFIELD_H_

#pragma once
#include "DisplayObject.h"
#include "io_utils.h"
#include <string>  
#include <sstream> 
#include <iostream>

class TextField :
	public DisplayObject
{
	string text;
	bool numeric;
public:
	//c'tors
	TextField()					:text(""),		numeric(false){};
	TextField(string s)			:text(s),		numeric(false){};
	TextField(TextField &tf) :text(tf.text), numeric(tf.numeric){}
	TextField(int num);
	//simple getters
	bool isNumeric(){ return numeric; }
	string getText() { return text; };

	//setters for both string and number
	void setText(string s);
	void setText(int num);
	virtual void render();
	void clear();
};


#endif