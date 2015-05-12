#ifndef _LIVESMETER_H_
#define _LIVESMETER_H_

const int MAX_COUNT = 5;
const int INIT_COUNT = 3;
const char HEART_CHAR = '\x03';

#pragma once
#include "TextField.h"

class Gauge :
	public TextField
{
	int count;
	char singleChar;
	bool rtl; //define which direction to draw the gauge

public:

	Gauge(char view = HEART_CHAR);;

	void setCount(int input);

	int getCount() { return count; };

	void setview(char view);

	void setRtl(bool val);
};


#endif