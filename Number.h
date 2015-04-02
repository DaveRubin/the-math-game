#ifndef _NUMBER_H_
#define _NUMBER_H_

#pragma once
#include "Actor.h"
class Number :
	public Actor
{
	int number = 10;
public:
	Number();
	Number(int numInput);
	Number(int numInput,int x, int y);
	virtual void render();
};

#endif
