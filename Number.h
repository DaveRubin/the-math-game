#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "Actor.h"

class Number :
	public Actor
{
	int number;
	int length;
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
