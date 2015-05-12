#include "Gauge.h"

void Gauge::setCount(int countInput){
	count = countInput;
	clear();
	//if right to left, then add spaces instead the missing lives
	string s = "";
	if (rtl) {
		s.append(INIT_LIVES - count, ' ');
	}
	//set hearts
	s.append(count, singleChar);
	setText(s);
}
