#ifndef _FLYER_H_
#define _FLYER_H_

#include "Actor.h"


class Flyer : public Actor
{
	char monsterStyle = '?';
	string direction;
	Point initPoint;

public:
	void setMonsterStyle(char symbol);							//set the symbol for the flyer
	void direct(string udlr){ direction = udlr; };				//set the direction for the flyer
	string getDirection(){ return direction; };


	virtual void move(bool reverse = false) override;
	virtual void onCollision(DisplayObject * ohterObject) override;
	void init();
	void setInitPoint(int x, int y);

	Flyer(string direction, int x, int y);
	~Flyer(){};
};

#endif