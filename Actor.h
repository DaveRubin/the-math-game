#pragma once
#include "DisplayObject.h"
#include "Direction.h"

class Actor:
	public DisplayObject
{
	const int DEFAULT_LIVES = 1;
	const char DEFAULT_LOOK = '\x06';

	char view;
	int lives;
	int direction = Direction::LEFT;
	
	void checkBounds();
public:
	Actor();
	Actor(char look, int lives);
	Actor(const Actor &actor);
	void move(bool reverse = false);
	virtual void render();
};

