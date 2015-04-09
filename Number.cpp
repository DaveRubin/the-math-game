#include "Number.h"


Number::Number()
{
	setType("Number");
	getLength();
	render();
}

Number::Number(int numInput)
{
	setType("Number");
	number = numInput;
	getLength();
	render();
}

Number::Number(int numInput, int x, int y)
{
	setType("Number");
	number = numInput;
	position.set(x, y);
	getLength();
	render();
}

void Number::getLength()
{
	length = 0;
	int tempInt = number;
	while (tempInt != 0)
	{
		length++;
		tempInt /= 10;
	}
	cout << "yeah" << endl;
}
void Number::render()
{
	gotoxy(position.getX(), position.getY());
	cout << number;
}

void Number::kill()
{
	if (getStage() != NULL)
	{
		getStage()->setChildAt(NULL, position.getX(), position.getY());
	}
	gotoxy(position.getX(), position.getY());
	for (int i = 0; i < length; i++)
	{
		cout << ' ';
	}
	hide();
}

