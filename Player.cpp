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
	hudLives = new Gauge(); 
	hudBullets = new Gauge(BULLET_LOOK);

	//redundent, should reconcider the architecture for identifieng objects
	setType("Player");
	objectType = "Player";

	score = 0;
	bulletRefillCounter = BULLET_REFILL_DURATION;
	setLives(PLAYER_INIT_LIVES);
	hudBullets->setCount(5);
	answeredRight = false;
}

void Player::shoot()
{
	int bulletsLeft = hudBullets->getCount();

	if (bulletsLeft > 0 && getDirection() != Direction::STAY )
	{
		//add bullet with the players location, and direction
		//then move it (to use move method warp logic)
		Bullet *newBullet = new Bullet();
		newBullet->position.set(position);
		newBullet->setDirection( getDirection() );
		getStage()->addChild(newBullet);
		newBullet->move();

		//reduce bullet count
		hudBullets->setCount(bulletsLeft - 1);
	}
}

void Player::addBullet()
{
	int bulletsLeft = hudBullets->getCount();

	if (bulletsLeft < 5)
	{
		hudBullets->setCount(bulletsLeft + 1);
	}
}

void Player::countTillRefill()
{
	int bulletsLeft = hudBullets->getCount();

	if (bulletsLeft < 5)
	{

		if (bulletRefillCounter == 0)
		{
			//reset counter and add bullet
			bulletRefillCounter = BULLET_REFILL_DURATION;
			addBullet();
		}

		else
		{
			bulletRefillCounter--;
		}
	}
}

/*
constructor 
defines how the player looks & its control keys
look - the char representing the player
tldrs - string of chars representing the keys for :top,left,down,right,shoot;
*/
Player::Player(char look = DEFAULT_ACTOR_LOOK , string tldrs = "waxdz")
{
	initStats();
	setView(look);

	if (tldrs.length() != 5)
		setKeys();

	else 
		setKeys(tldrs);
}

void Player::onIteration()
{
	//if bullets aren't full, then count tilll next refill
	countTillRefill();
}

/*
initialize the base parameters and update hudLives (to show the current lives)
*/
void Player::init()
{
	answeredRight = false;

	setLives(PLAYER_INIT_LIVES);
	hudLives->setCount(PLAYER_INIT_LIVES);
	hudBullets->setCount(5);
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

		if (hudEquation->trySolution(hitNumber))
		{
			if (hudEquation->isSolved())
			{
				score += NUMBER_SCORE;
				hudScore->setText(score);
				answeredRight = true;
			}
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