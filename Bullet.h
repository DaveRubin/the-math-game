#pragma once
#include "Actor.h"
class Bullet :
	public Actor
{
	char defaultBulletStyle = '*';
public:
	Bullet();
	~Bullet();
};

