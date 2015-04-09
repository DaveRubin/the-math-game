
#ifndef _ACTOR_H_
#define _ACTOR_H_

#pragma once
#include "DisplayObject.h"
#include "Direction.h"
#include "Stage.h"

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
	string objectType = "Actor";

	Actor();
	Actor(char look, int lives);
	Actor(const Actor &actor);

	void setDirection(int dir){ direction = dir; }
	int getDirection(){ return direction; }
	void setView(char c){ view = c; }


	virtual void move(bool reverse = false);
	virtual void checkCollision(){};
	bool collide(const Actor &actor);
	void stop();
	void clear();
	virtual void render();
};

#endif