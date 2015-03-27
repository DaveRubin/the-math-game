#include "Stage.h"

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
	numChildren++;
}

void Stage::render()
{
	for (int i = 0; i < numChildren; i++)
	{
		renderList[i]->render();
	}
}