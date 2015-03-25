#include "DisplayObject.h"


DisplayObject::~DisplayObject()
{

}

void DisplayObject::show()
{
	visible = true;
}

void DisplayObject::hide()
{
	visible = false;
}

bool DisplayObject::isVisible()
{
	return visible;
}

void DisplayObject::render()
{
	gotoxy(position.getX(), position.getY());
	cout << text  <<endl;
}