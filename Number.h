#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "Actor.h"

class Number :
	public Actor
{
	int number = 0;
	int length = 1;
	void getLength();

public:
	Number();
	Number(int numInput);
	Number(int numInput,int x, int y);
	virtual void render();
	virtual void kill();
	int getNumber(){ return number; }
	int getWidth(){ return length; }
};

#endif
