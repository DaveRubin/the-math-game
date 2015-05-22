#pragma once
#include "Player.h"

class Bullet :
	public Actor
{
public:
	Bullet();
	~Bullet();
	virtual void onCollision(DisplayObject *) override;
};

