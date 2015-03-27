#include "TextField.h"

void TextField::render(){
	gotoxy(position.getX(), position.getY());
	cout << text;
	setRedraw(false);
}

//clear current text
void TextField::clear()
{
	gotoxy(position.getX(), position.getY());
	string s = "";
	s.append(text.length(), ' ');
	cout << s;
}

//when changing text, 
//clear the current text
//change the text , and redraw again
void TextField::setText(string s)
{
	clear();
	text = s;
	cout << text;
}