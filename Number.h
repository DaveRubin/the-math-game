#pragma once
#include "Actor.h"
class Number :
	public Actor
{
	int number = 10;
public:
	Number();
	Number(int x, int y);
	virtual void render();
};

