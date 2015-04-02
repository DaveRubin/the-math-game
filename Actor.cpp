#include "Actor.h"


Actor::Actor()
{
	lives = DEFAULT_LIVES;
	view = DEFAULT_LOOK;
	setStatic(false);
}


Actor::Actor(char lookInput, int livesInput )
{
	lives = livesInput;
	view = lookInput;
}

Actor::Actor(const Actor &actor )
{
	lives = actor.lives;
	view = actor.view;
	position.set(actor.position);
}

void Actor::stop()
{
	direction = Direction::STAY;
}

void Actor::move( bool reverse )
{
	if (direction == Direction::STAY){
		setRedraw(false);
		return;
	}
	clear();
	int step = (reverse) ? -1 : 1;
	switch (direction)
	{
	case Direction::LEFT :
		position.add(Point(-step, 0));
		break;
	case Direction::RIGHT:
		position.add(Point(step, 0));
		break;
	case Direction::UP:
		position.add(Point(0, -step));
		break;
	case Direction::DOWN:
		position.add(Point(0, step));
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

void Actor::clear()
{
	gotoxy( position.getX(), position.getY() );
	cout << ' ';
}

void Actor::render()
{
	gotoxy( position.getX(), position.getY() );
	cout << view;
}

bool Actor::collide(const Actor &target)
{
	return ( position.equels( target.position ));
}