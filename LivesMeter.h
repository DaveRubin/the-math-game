#ifndef _LIVESMETER_H_
#define _LIVESMETER_H_

#define MAX_LIVES 5
#define INIT_LIVES 3

#define HEART_CHAR '\x03'

#pragma once
#include "TextField.h"
class LivesMeter :
	public TextField
{
	int lives;
	bool rtl; //define which direction to draw
public:
	LivesMeter() : rtl(false){ setLives(INIT_LIVES); };
	void setLives(int input);
	void setRtl(bool val){ 
		rtl = val; 
		setLives(lives);
	}
};


#endif