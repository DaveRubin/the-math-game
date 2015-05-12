#include "Gauge.h"

Gauge::Gauge(char view): singleChar(view), rtl(false)
{
	setCount(INIT_COUNT);
}

void Gauge::setCount(int countInput)
{
	count = countInput;
	clear();

	//if right to left, then add spaces instead the missing lives
	string s = "";

	if (rtl) {
		s.append(INIT_COUNT - count, ' ');
	}

	//set hearts
	s.append(count, singleChar);
	setText(s);
}

void Gauge::setview(char view)
{
	singleChar = view;
	setCount(count);
}

void Gauge::setRtl(bool val)
{ 
	rtl = val; 
	setCount(count);
}