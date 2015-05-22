#pragma once
#include "Actor.h"

class NumbersEater :
	public Actor
{
	char monster_style = '%';

public:

	NumbersEater();
	~NumbersEater();
	virtual void move(bool reverse = false) override;
	virtual void onCollision(DisplayObject *) override;
};

