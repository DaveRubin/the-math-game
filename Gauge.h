#ifndef _LIVESMETER_H_
#define _LIVESMETER_H_

#define MAX_LIVES 5
#define INIT_LIVES 3

#define HEART_CHAR '\x03'

#pragma once
#include "TextField.h"
class Gauge :
	public TextField
{
	int count;
	char singleChar;
	bool rtl; //define which direction to draw
public:
	Gauge(char view = HEART_CHAR) : singleChar(view), rtl(false){ setCount(INIT_LIVES); };

	void setCount(int input);

	void setview(char view)
	{
		singleChar = view;
		setCount(count);
	};

	void setRtl(bool val){ 
		rtl = val; 
		setCount(count);
	}
};


#endif