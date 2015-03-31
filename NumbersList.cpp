#include "NumbersList.h"


void NumbersList::addNumber(Number *child)
{
	//if child list is full, multiply size
	if (numChildren == listSize){
		if (listSize == 0)
			listSize = 1;
		listSize *= 2;

		//craete a temp array and move all children to the new one
		Number **newArr = new Number*[listSize];
		for (int i = 0; i < numChildren; i++)
		{
			newArr[i] = numbers[i];
		}
		if (listSize > 2) delete numbers;
		numbers = newArr;
	}

	//then add the child at the end of the list
	numbers[numChildren] = child;
	numChildren++;
}
