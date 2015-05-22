#include "Stage.h"


Stage::Stage()
{
	numChildren = 0;
	renderListSize = 0;
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
Point Stage::getNearestNumberPosition(const Point &position)
{
	return Point();
}

void  Stage::setChildAt(DisplayObject *child, int x, int y)
{
	matrix[x][y] = child;
}

void Stage::addChild(DisplayObject *child)
{
	//if child list is full, multiply size
	if (numChildren == renderListSize){
		if (renderListSize == 0) 
			renderListSize = 1;
		renderListSize *= 2;

		//craete a temp array and move all children to the new one
		DisplayObject **newArr = new DisplayObject*[renderListSize];
		for (int i = 0; i < numChildren; i++)
		{
			newArr[i] = renderList[i];
		}
		if (renderListSize > 2) delete renderList;
		renderList = newArr;
	}

	//then add the child at the end of the list
	renderList[numChildren] = child;

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
	numChildren++;
}

void Stage::render()
{
	for (int i = 0; i < numChildren; i++)
	{
		if (renderList[i]->isVisible())
			renderList[i]->render();
	}
}

void Stage::clear()
{
	for (int i = 0; i < numChildren; i++)
	{
		renderList[i]->clear();
	}
}

void Stage::moveChildren()
{
	for (int i = 0; i < numChildren; i++)
	{
		if (!renderList[i]->isStatic())
		{
			static_cast<Actor*>(renderList[i])->move();
		}
	}
}

void Stage::seconderyMove()
{
	for (int i = 0; i < numChildren; i++)
	{
		if (!renderList[i]->isStatic() && renderList[i]->isFastObject() )
		{
			static_cast<Actor*>(renderList[i])->move();
		}
	}
}

// TODO: need to handle child removal properly, the program is crashing because stage deleted child
//should remove the specific child from the list, not 
void Stage::removeChildren(DisplayObject *child)
{
	bool removed = false;
	for (int i = 0; i < numChildren; i++)
	{
		if (removed){
			renderList[i] = renderList[i + 1];
		}
		if (renderList[i] == child){
			//delete child  --old code, crashed the program
			renderList[i] = NULL;
			//TODO:
			//whenever removing children from the list, we should oreder the rest of the list (make splice)
			//numChildren--;
			removed = true;
		}

	}

}

void Stage::init()
{
	deleteAll();
	numChildren = 0;
	resetMatrix();
}

void Stage::deleteAll()
{
	for (int i = 0; i < numChildren; i++)
	{
		renderList[i] = NULL;
		//delete renderList[i];
	}
}