#include "Bullet.h"


void Bullet::setDirection(int dir)
{
	//first use base class to change the actual direction
	Actor::setDirection(dir);

	//now change the look view to look like its facing the right direction
	if (dir == Direction::LEFT || dir == Direction::RIGHT )
	{
		setView('-');
	}
	else if (dir == Direction::UP || dir == Direction::DOWN)
	{
		setView('|');
	}
}

Bullet::Bullet()
{
	setView(defaultBulletStyle);
}


Bullet::~Bullet()
{

}
