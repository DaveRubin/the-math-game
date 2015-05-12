
#ifndef _ACTOR_H_
#define _ACTOR_H_


#define DEFAULT_ACTOR_LIVES  1
#define DEFAULT_ACTOR_LOOK  '\x02'

#pragma once
#include "DisplayObject.h"
#include "Direction.h"
#include "Stage.h"

class Actor:
	public DisplayObject
{
	char view;
	int lives;
	int direction;
	
	void checkBounds();
public:
	string objectType;

	Actor();
	Actor(char look, int lives);
	Actor(const Actor &actor);

	void setDirection(int dir){ direction = dir; }
	int getDirection(){ return direction; }
	void setView(char c){ view = c; }


	int getLives(){ return lives; }
	void setLives(int count){ lives = count; }

	bool collide(const Actor &actor);
	void stop();
	void clear();

	virtual void move(bool reverse = false);
	virtual void checkCollision();
	virtual void onCollision(DisplayObject *);
	virtual void render();
	virtual void hit();
	virtual void kill();
};

#endif