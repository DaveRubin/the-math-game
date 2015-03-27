#include "TextField.h"

void TextField::render(){
	gotoxy(position.getX(), position.getY());
	cout << text;
	setRedraw(false);
}