
#ifndef _COLLISION_MANAGER_
#define _COLLISION_MANAGER_

#pragma once
class Actor;
class DisplayObject;
#include "Number.h"
/*
Service that handles all objects collisions
*/


class CollisionManager
{
public:

//	static void collide(Player *p1, Player *p2);
//	static void collide(Player *player, Number *number);
//	static void collide(Number *numberp1, Player *player);
//	static void collide(Actor *actor, Actor *actor2) {};
	static void collide(DisplayObject *actor, DisplayObject *actor2) {};
	CollisionManager();
	~CollisionManager();
};


#endif