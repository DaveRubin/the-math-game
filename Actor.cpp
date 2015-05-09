#include "Actor.h"


Actor::Actor()
{
	setType("Actor");
	lives = DEFAULT_ACTOR_LIVES;
	view = DEFAULT_ACTOR_LOOK;
	setStatic(false);
	objectType = "Actor";
	direction = Direction::STAY;
}


Actor::Actor(char lookInput, int livesInput )
{
	setType("Actor");
	lives = livesInput;
	view = lookInput;
	objectType = "Actor";
	direction = Direction::STAY;
}

Actor::Actor(const Actor &actor )
{
	setType("Actor");
	lives = actor.lives;
	view = actor.view;
	position.set(actor.position);
	objectType = "Actor";
	direction = Direction::STAY;
}

void Actor::stop()
{
	direction = Direction::STAY;
}

void Actor::kill()
{
	stop();
	clear();
	hide();
}

void Actor::move( bool reverse )
{
	if (lives <= 0) return;

	checkCollision();

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
	getStage()->setChildAt(this, position.getX(), position.getY());
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
	getStage()->setChildAt(NULL, position.getX(), position.getY());
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