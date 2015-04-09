#ifndef _LIVESMETER_H_
#define _LIVESMETER_H_

#pragma once
#include "TextField.h"
class LivesMeter :
	public TextField
{
	const int MAX_LIVES = 5;
	const char HEART = '\x03';
	const int INIT_LIVES = 3;
	int lives = INIT_LIVES;
	bool rtl = false; //define which direction to draw
public:
	LivesMeter(){ setLives(INIT_LIVES); };
	void setLives(int input);
	void setRtl(bool val){ 
		rtl = val; 
		setLives(lives);
	}
};


#endif