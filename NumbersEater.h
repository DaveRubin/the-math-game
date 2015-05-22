#pragma once
#include "Actor.h"
#include "Number.h"

class NumbersEater :
	public Actor
{
	char monsterStyle = '%';
	void normalizeDeltas(int &delta_x, int &delta_y);
	Point initPoint;
	void commonInits();
public:

	NumbersEater();
	NumbersEater(int x, int y);
	~NumbersEater();

	void setInitPoint(int x, int y);

	virtual void move(bool reverse = false) override;
	virtual void onCollision(DisplayObject *) override;
	void init();
};

