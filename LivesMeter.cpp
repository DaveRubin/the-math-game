#include "LivesMeter.h"

void LivesMeter::setLives(int count){
	text = "";
	//if right to left, then add spaces instead the missing lives
	if (rtl){
		text.append(INIT_LIVES - lives, ' ');
	}
	//set hearts
	text.append(lives, HEART);
}