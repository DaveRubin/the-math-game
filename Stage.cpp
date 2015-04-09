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
	child->setStage(this);
	matrix[child->position.getX()][child->position.getY()] = child;
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