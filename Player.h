#ifndef _PLAYER_H_
#define _PLAYER_H_

#pragma once
#include "Actor.h"
#include "Stage.h"
#include "Number.h"
#include "Equation.h"
#include "LivesMeter.h"
#include "TextField.h"



class Player : public Actor
{
	

	int score;
	char keyUp;
	char keyLeft;
	char keyDown;
	char keyRight;

	Equation *hudEquation;
	TextField *hudScore;
	LivesMeter *hudLives;

	void setKeys(string tldr);
	void initStats();
public:
	string objectType;
	bool answeredRight;

	Player(char look,string keys);

	void checkKey(char option) {
		//if key is valid movement key, then set direction
		//we use normal char and not const to allow users to define their own keys
		if (option == keyUp) setDirection(Direction::UP);
		if (option == keyLeft) setDirection(Direction::LEFT);
		if (option == keyDown) setDirection(Direction::DOWN);
		if (option == keyRight) setDirection(Direction::RIGHT);
	}
	virtual void checkCollision() override;
	Equation *getEquation(){ return hudEquation; };
	TextField *getScore(){ return hudScore; };
	LivesMeter *getLivesObj(){ return hudLives; };

	void init();
};


#endif