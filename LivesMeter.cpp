#include "LivesMeter.h"

void LivesMeter::setLives(int count){
	lives = count;
	clear();
	//if right to left, then add spaces instead the missing lives
	string s = "";
	if (rtl){
		s.append(INIT_LIVES - lives, ' ');
	}
	//set hearts
	s.append(lives, HEART);
	setText(s);
}
