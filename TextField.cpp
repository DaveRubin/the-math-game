#include "TextField.h"


TextField::~TextField()
{
}


void TextField::render()
{
	gotoxy(position.getX(), position.getY());
	cout << text  <<endl;
}