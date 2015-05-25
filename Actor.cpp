#include "Actor.h"


Actor::Actor()
{
	setType("Actor");
	lives = DEFAULT_ACTOR_LIVES;
	view = DEFAULT_ACTOR_LOOK;
	setColor(DEFAULT_COLOR);
	setStatic(false);
	objectType = "Actor";
	direction = Direction::STAY;
}


Actor::Actor(char lookInput, int livesInput )
{
	setColor(DEFAULT_COLOR);
	setType("Actor");
	lives = livesInput;
	view = lookInput;
	objectType = "Actor";
	direction = Direction::STAY;
}

Actor::Actor(const Actor &actor )
{
	setColor(DEFAULT_COLOR);
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

	if (direction == Direction::STAY) {
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
	position.warp();
	getStage()->setChildAt(this, position.getX(), position.getY());
}

void Actor::checkCollision()
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

	tmpPos.warp();

	//get matrix and check if something is there
	DisplayObject *targetObj = getStage()->getChildAt(tmpPos.getX(), tmpPos.getY());
	//if clear then return
	if (targetObj == NULL) return;

	string targetType = targetObj->getType();
	onCollision(targetObj);
	CollisionManager::collide(this, targetObj);
}

//TODO: make this function =0 so that Actor would become abstract class
void Actor::onCollision(DisplayObject * targetObj)
{

}

void Actor::clear()
{
	gotoxy( position.getX(), position.getY() );
	getStage()->setChildAt(NULL, position.getX(), position.getY());
	cout << ' ';
}

void Actor::hit()
{
	lives--;
	if (lives == 0) kill();
}

void Actor::render()
{
	setTextColor(getColor());
	gotoxy( position.getX(), position.getY() );
	cout << view;
	setTextColor(DEFAULT_COLOR);
}

bool Actor::collide(const Actor &target)
{
	return ( position.equels( target.position ));
}