#include "Number.h"


Number::Number()
{
	position.set(0, 0);
	render();
}


Number::Number(int x, int y)
{
	position.set(x, y);
	render();
}

void Number::render()
{
	gotoxy(position.getX(), position.getY());
	cout << number;
}

