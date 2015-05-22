#include "NumbersEater.h"


void NumbersEater::commonInits()
{
	setView(monsterStyle);
	setType("NumbersEater");
	setStatic(false);
	setDirection(Direction::RIGHT);
}

NumbersEater::NumbersEater()
{
	commonInits();
	setInitPoint(0, 0);
}

NumbersEater::NumbersEater(int x, int y)
{
	commonInits();
	setInitPoint(x, y);
}

NumbersEater::~NumbersEater()
{

}

void NumbersEater::setInitPoint(int x, int y)
{
	initPoint = Point(x, y);
	position.set(x, y);
}

/*
normalize distance to allow proper warp
*/
void NumbersEater::normalizeDeltas( int& deltaX,  int& deltaY)
{
	if (abs(deltaX) >= SCREEN_WIDTH / 2)
	{
		if (deltaX < 0) deltaX += SCREEN_WIDTH;
		else deltaX -= SCREEN_WIDTH;
	}

	if (abs(deltaY) >= STAGE_HEIGHT / 2)
	{
		if (deltaY < 0) deltaY += STAGE_HEIGHT;
		else deltaY -= STAGE_HEIGHT;
	}
}

void NumbersEater::move(bool reverse)
{
	//find nearest number
	DisplayObject *nearestNumberPosition = getStage()->getNearestNumberTo(position);
	int deltaX;
	int deltaY;
	//set direction to it
	if (nearestNumberPosition != NULL )
	{
		deltaX = nearestNumberPosition->position.getX() - position.getX();
		deltaY = nearestNumberPosition->position.getY() - position.getY();

		//normalize distances in case of warp
		normalizeDeltas(deltaX,deltaY);

		//set direction according to the delta
		if (deltaX > 0) 
			setDirection(Direction::RIGHT);
		else if (deltaX < 0) 
			setDirection(Direction::LEFT);
		else if (deltaY > 0) 
			setDirection(Direction::DOWN);
		else if (deltaY < 0) 
			setDirection(Direction::UP);
	}
	//call actor move
	Actor::move();
}


void NumbersEater::onCollision(DisplayObject *hitObject )
{
	//if collided with Number, kill both
	//if with bullet kill bullet (monsters are bullet proof)
	//anything else, Kill monster
	if (hitObject->getType() == "Number")
	{
		hitObject->kill();
		this->kill();
	}
	else if (hitObject->getType() == "Bullet")
		hitObject->kill();
	else
		this->kill();
}

void NumbersEater::init()
{
	show();
	position.set(initPoint);
}