#include "Number.h"


Number::Number()
{
	render();
}

Number::Number(int numInput)
{
	number = numInput;
	render();
}

Number::Number(int numInput, int x, int y)
{
	number = numInput;
	position.set(x, y);
	render();
}

void Number::render()
{
	gotoxy(position.getX(), position.getY());
	cout << number;
}

