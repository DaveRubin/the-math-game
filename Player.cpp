#include "Player.h"
/**
set the movement keys (top, left down ,right)

*/
void Player::setKeys(string tldr = "waxd")
{
	keyUp =		tldr[0];
	keyLeft =	tldr[1];
	keyDown =	tldr[2];
	keyRight =	tldr[3];
}

/*
initialize player stats
*/
void Player::initStats()
{
	hudEquation = new Equation();
	hudScore = new TextField(0);
	hudLives = new LivesMeter();
	setType("Player");
	score = 0;
	setLives(PLAYER_INIT_LIVES);
	objectType = "Player";
	answeredRight = false;
}

/*
constructor that defines how the player looks & its keyboard
look - the char representing the player
tldr - string of chars representing the keys for :top,left,down,right;
*/
Player::Player(char look = DEFAULT_ACTOR_LOOK , string tldr = "waxd")
{
	initStats();
	setView(look);
	if (tldr.length() != 4)
		setKeys();
	else {
		setKeys(tldr);
	}
}


/*
initialize the base parameters
*/
void Player::init()
{
	setLives(PLAYER_INIT_LIVES);
	setDirection(Direction::STAY);
	answeredRight = false;
	show();
}

/*
check collision
check the next position of the player using its current position and direction
then if there is some actor at this point handle it by its type:

if other player then stop
if number, then check validity of number and get points\reduce 

*/
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
	DisplayObject *targetObj = getStage()->getChildAt(tmpPos.getX(), tmpPos.getY());
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
		int hitNumber = static_cast<Number*>(targetObj)->getNumber();
		targetObj->kill();

		if (hitNumber == hudEquation->getSolution())
		{
			score += NUMBER_SCORE;
			hudScore->setText(score);
			answeredRight = true;
		}
		else
		{		
			setLives(getLives() - 1);
			hudLives->setLives(getLives());
			if (getLives() == 0){
				kill();
			}
		}
	}
}