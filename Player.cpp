#include "Player.h"

/**
set the movement keys (top, left down ,right,shoot)
*/
void Player::setKeys(string tldr = "waxdz")
{
	keyUp =		tldr[0];
	keyLeft =	tldr[1];
	keyDown =	tldr[2];
	keyRight =	tldr[3];
	keyShoot =	tldr[4];
}

/*
initialize player stats
*/
void Player::initStats()
{
	hudEquation = new Equation();
	hudScore = new TextField(0);
	//TODO: add gauges look from config 
	hudLives = new Gauge(); 
	bulletCount = new Gauge('*');

	//redundent, should reconcider the architecture for identifieng objects
	setType("Player");
	objectType = "Player";

	score = 0;
	setLives(PLAYER_INIT_LIVES);
	bulletCount->setCount(5);
	answeredRight = false;
}

void Player::shoot()
{
	int shotsLeft = bulletCount->getCount();

	if (shotsLeft > 0)
	{
		//add bullet with the players direction

		bulletCount->setCount(shotsLeft - 1);
	}
}

void Player::addBullet()
{
	int shotsLeft = bulletCount->getCount();

	if (shotsLeft < 5)
	{
		bulletCount->setCount(shotsLeft + 1);
	}
}

/*
constructor that defines how the player looks & its keyboard
look - the char representing the player
tldr - string of chars representing the keys for :top,left,down,right,shoot;
*/
Player::Player(char look = DEFAULT_ACTOR_LOOK , string tldrs = "waxdz")
{
	initStats();
	setView(look);
	if (tldrs.length() != 5)
		setKeys();
	else {
		setKeys(tldrs);
	}
}


/*
initialize the base parameters and update hudLives (to show the current lives)
*/
void Player::init()
{
	answeredRight = false;

	setLives(PLAYER_INIT_LIVES);
	hudLives->setCount(PLAYER_INIT_LIVES);
	setDirection(Direction::STAY);

	show();
}

/*
the function gets  the display obj
*/
void Player::onCollision(DisplayObject *targetObj)
{
	string targetType = targetObj->getType();
	//if other player stop
	//TODO: move the objectType string into const class
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
			hit();
		}
	}
}

void Player::hit()
{
	//update lives
	setLives(getLives() - 1);
	hudLives->setCount(getLives());

	//if no lives left then kill player
	if (getLives() == 0)
	{
		kill();
	}
}