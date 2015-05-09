#pragma once
#include "Actor.h"
class Bullet :
	public Actor
{
	char defaultBulletStyle = '\u25CF';
public:
	void setDirection(int dir);
	Bullet();
	~Bullet();
};

