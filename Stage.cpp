#include "Stage.h"


Stage::Stage()
{
	resetMatrix();
}

void Stage::resetMatrix(){
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			matrix[i][j] = NULL;
		}
	}
}

DisplayObject * Stage::getChildAt(int x, int y)
{
	return matrix[x][y];
}

DisplayObject * Stage::getChildAt(Point p)
{
	return matrix[p.getX()][p.getY()];
}

/*
this function probes the matrix for the nearest Number object to the given Point
*/
DisplayObject *Stage::getNearestNumberTo(Point position)
{
	bool showProbes = false;

	Point left, right;
	Point *nearestNumber = NULL;
	DisplayObject *tmpObject = NULL;

	int maxLevel = SCREEN_WIDTH;
	int positionX = position.getX();
	int positionY = position.getY();

	//we wil go level by level, from "y-level --> y+level" and the X will go from 0 to level and back
	int xSpread = 0;
	Point tmpPoint;

	for (int level = 1; level < maxLevel; level++)
	{
		for (int i = -level; i <= level; i++)
		{
			xSpread = level - abs(i);
			left.set(positionX - xSpread, positionY + i);
			right.set(positionX + xSpread, positionY + i);
			tmpPoint = left;
			left.warp();
			right.warp();

			int tmp = left.getY();

			if (showProbes)
			{
				gotoxy(left.getX(), left.getY());
				cout << "X";
				gotoxy(right.getX(), right.getY());
				cout << "X";
			}

			tmpObject = NULL;
			tmpObject = getChildAt(left);

			if (tmpObject != NULL  && tmpObject->getType() == "Number" )
			{
				nearestNumber = &(tmpObject->position);
				break;
			}

			if (nearestNumber == NULL && !left.equels(right))
			{
				tmpObject = NULL;
				tmpObject = getChildAt(left);
				if (tmpObject != NULL  && tmpObject->getType() == "Number")
				{
					nearestNumber = &(tmpObject->position);
					break;
				}
			}
		}

		if (nearestNumber != NULL) break;
	}
	
	return tmpObject;
}

void  Stage::setChildAt(DisplayObject *child, int x, int y)
{
	matrix[x][y] = child;
}

void Stage::addChild(DisplayObject *child)
{
	renderList.push_front(child);

	//inject the stage to the child
	child->setStage(this);

	//now add the clid reference to the matrix
	//if its a number longer then 1 digit, add mutiple 
	for (int i = 0; i < child->getWidth(); i++)
	{
		int xPos = child->position.getX() + i;
		if (xPos >= SCREEN_WIDTH) break;
		matrix[xPos][child->position.getY()] = child;
	}
}

void Stage::render()
{
	DisplayObject *tmpObj;

	for (list<DisplayObject*>::iterator it = renderList.begin(); it != renderList.end(); it++)
	{
		tmpObj = (*it);

		if (tmpObj->isVisible())
			tmpObj->render();
	}
}

void Stage::clearDeadChildren()
{
	DisplayObject *killTarget;

	for (list<DisplayObject*>::iterator it = killList.begin(); it != killList.end(); it++)
	{
		killTarget = (*it);
		renderList.remove(killTarget);
	}
	killList.clear();
}

void Stage::clear()
{
	for (list<DisplayObject*>::iterator it = renderList.begin(); it != renderList.end(); it++)
		(*it)->clear();
}

void Stage::moveChildren()
{
	DisplayObject *tmpObj;

	for (list<DisplayObject*>::iterator it = renderList.begin(); it != renderList.end(); it++)
	{
		tmpObj = (*it);

		if (! tmpObj->isStatic())
			static_cast<Actor*>(tmpObj)->move();
	}

	clearDeadChildren();
}

void Stage::seconderyMove()
{
	DisplayObject *tmpObj;

	for (list<DisplayObject*>::iterator it = renderList.begin(); it != renderList.end(); it++)
	{

		tmpObj = (*it);

		if (!tmpObj->isStatic() && tmpObj->isFastObject())
			static_cast<Actor*>(tmpObj)->move();
	}

	clearDeadChildren();
}

void Stage::removeChildren(DisplayObject *child)
{
	killList.push_front(child);
}

void Stage::init()
{
	deleteAll();
	resetMatrix();
}

void Stage::deleteAll()
{
	renderList.clear();
}