#pragma once
#include "Player.h"

class Bullet :
	public Actor
{
	char defaultBulletStyle = '*';
public:
	Bullet();
	~Bullet();
	virtual void onCollision(DisplayObject *) override;
};

