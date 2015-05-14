#include "Bullet.h"

//set look to '*' according to instructions
Bullet::Bullet()
{
	setColor(Color::LIGHTCYAN);
	setView(defaultBulletStyle);
	setType("Bullet");
	objectType = "Bullet";
	setFast(true);
}


Bullet::~Bullet()
{

}

void Bullet::onCollision(DisplayObject* targetObj)
{

	string targetType = targetObj->getType();
	
	if (targetType == "Player")
	{
		//add collision logic
		static_cast<Actor*>(targetObj)->hit();
		kill();
	}

	if (targetType == "Number")
	{
		targetObj->kill();
		kill();
	}

}