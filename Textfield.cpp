#include "TextField.h"

TextField::TextField(int num)
{
	setColor(DEFAULT_COLOR);
	setText(num);
}

void TextField::render()
{
	gotoxy(position.getX(), position.getY());

	setTextColor(getColor());
	cout << text;
	setTextColor(DEFAULT_COLOR);

	setRedraw(false);
}

//clear current text
void TextField::clear()
{
	gotoxy(position.getX(), position.getY());
	string s = "";
	s.append(text.length(), ' ');
	cout << s;
	gotoxy(position.getX(), position.getY());
}

//when changing text, 
//clear the current text
//change the text , and redraw again
void TextField::setText(string s)
{
	clear();
	numeric = false;
	text = s;

	setTextColor(getColor());
	cout << text;
	setTextColor(DEFAULT_COLOR);
}
//when changing text, 
//clear the current text
//change the text , and redraw again
void TextField::setText(int num)
{
	clear();
	numeric = true;
	stringstream sstm;
	sstm << num;
	text =  sstm.str();
}
