#include "Actor.h"


Actor::Actor()
{
	lives = DEFAULT_LIVES;
	view = DEFAULT_LOOK;
}


Actor::Actor(char lookInput, int livesInput)
{
	lives = livesInput;
	view = lookInput;
}

Actor::Actor(const Actor &actor)
{
	lives = actor.lives;
	view = actor.view;
	position.set(actor.position);
}


void Actor::move(bool reverse)
{
	switch (direction)
	{
	case Direction::STAY:
		setRedraw(false);
		return;
		break;

	case Direction::LEFT :
		position.add(Point(-1, 0));
		break;
	case Direction::RIGHT:
		position.add(Point(1, 0));
		break;
	case Direction::UP:
		position.add(Point(0, -1));
		break;
	case Direction::DOWN:
		position.add(Point(0, 1));
		break;
	}

	setRedraw(true);
	checkBounds();

}

void Actor::checkBounds()
{
	//check out of bounds
	int currentX = position.getX();
	int currentY = position.getY();

	if (currentX >= SCREEN_WIDTH) 
		position.set(Point( 0, currentY));
	else if (currentX < 0) 
		position.set(Point(SCREEN_WIDTH -1 , currentY));

	if (currentY > SCREEN_HEIGHT )
		position.set(Point(currentX, HUD_HEIGHT));
	else if (currentY < HUD_HEIGHT)
		position.set(Point(currentX, SCREEN_HEIGHT));
}

void Actor::render()
{
	int xPos = position.getX();
	gotoxy(position.getX(), position.getY());
	cout << view;
}