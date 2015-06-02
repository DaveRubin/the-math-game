#ifndef _PLAYER_H_
#define _PLAYER_H_

#pragma once
#include "Actor.h"
#include "Stage.h"
#include "Number.h"
#include "Equation.h"
#include "Gauge.h"
#include "TextField.h"
#include "Bullet.h"



class Player : public Actor
{
	int score;
	int bulletRefillCounter;
	char keyUp;
	char keyLeft;
	char keyDown;
	char keyRight;
	char keyShoot;

	Equation *hudEquation;
	TextField *hudScore;
	Gauge *hudLives;
	Gauge *hudBullets;
	Point initPoint;

	void setKeys(string tldr);
	void initStats();
	void shoot();
	void addBullet();
	void countTillRefill();

public:
	//public vars
	string objectType;
	bool answeredRight;

	//player must get control keys top , left, down, right
	Player(char look,string keys);

	void checkKey(char option) {

		//if key is valid movement key, then set direction
		//we use normal char and not const to allow users to define their own keys
		if (option == keyUp) setDirection(Direction::UP);
		if (option == keyLeft) setDirection(Direction::LEFT);
		if (option == keyDown) setDirection(Direction::DOWN);
		if (option == keyRight) setDirection(Direction::RIGHT);

		if (option == keyShoot) shoot();
	}

	//additional actions to be taken each iteration
	void onIteration();

	Equation *getEquation() { return hudEquation; };
	TextField *getScore() { return hudScore; };
	Gauge *getLivesObj() { return hudLives; };
	Gauge *getBulletsObj() { return hudBullets; };
	void setInitPoint(Point init) { initPoint = init; };
	Point getInitPoint() { return initPoint; };

	void init();
	virtual void onCollision(DisplayObject *) override;
	virtual void hit() override;
	virtual void kill() override;

};


#endif