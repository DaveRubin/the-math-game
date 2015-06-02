#include "Bullet.h"

//set look to '*' according to instructions
Bullet::Bullet()
{
	setColor(Color::LIGHTCYAN);
	setView(BULLET_LOOK);
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
		
		Player * player = static_cast<Player*>(targetObj);
		//erase from previous location
		player->clear();

		//move player to initial location
		player->position.set(player->getInitPoint());
		kill();
	}

	if (targetType == "Number")
	{
		targetObj->kill();
		kill();
	}

}