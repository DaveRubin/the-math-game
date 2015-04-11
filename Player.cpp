#include "Player.h"

void Player::setDefaultKeys()
{
	keyUp = 'w';
	keyLeft = 'a';
	keyDown = 's';
	keyRight = 'd';
}

void Player::initStats()
{
	hudEquation = new Equation();
	hudScore = new TextField(0);
	hudLives = new LivesMeter();
	setType("Player");
	score = 0;
	setLives(PLAYER_INIT_LIVES);
}

Player::Player()
{
	initStats();
	setDefaultKeys();
}


Player::Player(char look)
{
	initStats();
	setView(look);
	setDefaultKeys();
}


Player::Player(char look, string tldr)
{
	initStats();
	setView(look);
	if (tldr.length() != 4)
		setDefaultKeys();
	else {
		keyUp = tldr[0];
		keyLeft = tldr[1];
		keyDown = tldr[2];
		keyRight = tldr[3];
	}
}

void Player::checkCollision()
{
	int step = 1;
	Point tmpPos = Point(position);
	//move tmpPoint
	switch (getDirection())
	{
	case Direction::LEFT:
		tmpPos.add(Point(-step, 0));
		break;
	case Direction::RIGHT:
		tmpPos.add(Point(step, 0));
		break;
	case Direction::UP:
		tmpPos.add(Point(0, -step));
		break;
	case Direction::DOWN:
		tmpPos.add(Point(0, step));
		break;
	}
	//get matrix and check if something is there
	Stage *stagePnt = getStage();
	DisplayObject *targetObj = stagePnt->getChildAt(tmpPos.getX(), tmpPos.getY());
	//if clear then return
	if (targetObj == NULL) return;
	string targetType = targetObj->getType();
	//if other player stop
	if (targetType == "Player")
	{
		setDirection(Direction::STAY);
	}
	//if number then kill the number
	if (targetType == "Number")
	{
		targetObj->kill();
		score += NUMBER_SCORE;
		hudScore->setText(score);
		//setDirection(Direction::STAY);
	}
}