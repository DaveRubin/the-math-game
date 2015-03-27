#pragma once
#include "Actor.h"



class Player :
	public Actor
{
	

	int score;
	char keyUp;
	char keyLeft;
	char keyDown;
	char keyRight;

	void setDefaultKeys();
public:
	Player();
	Player(char);
	Player(char,string);
	void checkKey(char option) {
		//if key is valid movement key, then set direction
		//we use normal char and not const to allow users to define their own keys
		if (option == keyUp) setDirection(Direction::UP);
		if (option == keyLeft) setDirection(Direction::LEFT);
		if (option == keyDown) setDirection(Direction::DOWN);
		if (option == keyRight) setDirection(Direction::RIGHT);
	}
	int getScore(){ return score; }
};

