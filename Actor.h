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
	int direction = Direction::RIGHT;
	
	void checkBounds();
public:
	Actor();
	Actor(char look, int lives);
	Actor(const Actor &actor);
	void move(bool reverse = false);
	void clear();
	virtual void render();
};

