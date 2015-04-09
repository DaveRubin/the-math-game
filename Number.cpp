#include "Number.h"


Number::Number()
{
	setType("Number");
	render();
}

Number::Number(int numInput)
{
	setType("Number");
	number = numInput;
	render();
}

Number::Number(int numInput, int x, int y)
{
	setType("Number");
	number = numInput;
	position.set(x, y);
	render();
}

void Number::render()
{
	gotoxy(position.getX(), position.getY());
	cout << number;
}

