#pragma once
#include "DisplayObject.h"
class LivesMeter :
	public DisplayObject
{
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

