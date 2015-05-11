#include "Bullet.h"

//set look to '*' according to instructions
Bullet::Bullet()
{
	setView(defaultBulletStyle);
	setType("Bullet");
	objectType = "Bullet";
	setFast(true);
}


Bullet::~Bullet()
{

}
