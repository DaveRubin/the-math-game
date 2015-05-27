#include "Flyer.h"


void Flyer::setMonsterStyle(char symbol)
{
	monsterStyle = symbol;
}

void Flyer::move(bool reverse)
{
	string udlr = getDirection();
	if (udlr.compare("right") == 0)
		setDirection(Direction::RIGHT);
	else if (udlr.compare("left") == 0)
		setDirection(Direction::LEFT);
	else if (udlr.compare("down") == 0)
		setDirection(Direction::DOWN);
	else if (udlr.compare("up") == 0)
		setDirection(Direction::UP);


	Actor::move();
}

//Flyers kill anything in their path
void Flyer::onCollision(DisplayObject* otherObject)
{
	if (!otherObject->getType().compare("Flyer") == 0)
		otherObject->kill();
}

void Flyer::init()
{
	show();
	position.set(initPoint);
}

//Set the location for the Flyer
void Flyer::setInitPoint(int x, int y)
{
	initPoint = Point(x, y);
	position.set(x,y);
}

//Constructor 
Flyer::Flyer(string direct, int x, int y)
{
	//set direction
	Flyer::direct(direct);

	//appearance changes in light of direction..
	if (direction == "up" || direction == "down")
		setMonsterStyle('$');
	else if (direction == "right" || direction == "left")
	{
		setMonsterStyle('!');
		setFast(true);
	}
		
	//set appearance
	setView(monsterStyle);
	setColor(RED);
	
	//set type
	setType("Flyer");

	//is moving actor
	setStatic(false);

	//set spawn location
	setInitPoint(x,y);

	//add to display
	show();
}