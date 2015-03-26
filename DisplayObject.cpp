#include "DisplayObject.h"

void DisplayObject::render()
{
	gotoxy(position.getX(), position.getY());
	cout << text  <<endl;
}