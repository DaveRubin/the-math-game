#pragma once
#include "DisplayObject.h"
#include "Direction.h"

class Actor:
	public DisplayObject
{
	const int DEFAULT_LIVES = 1;
	const char DEFAULT_LOOK = '\x02';

	char view;
	int lives;
	int direction = Direction::STAY;
	
	void checkBounds();
public:

	Actor();
	Actor(char look, int lives);
	Actor(const Actor &actor);

	void setDirection(int dir){ direction = dir; }
	int getDirection(){ return direction; }
	void setView(char c){ view = c; }


	void move(bool reverse = false);
	void clear();
	virtual void render();
};

