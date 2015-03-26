#include "Point.h"

float Point::distance(Point p)
{
	int deltaX = abs(p.getX() - x );
	int deltaY = abs( p.getY() - y);
	return sqrtf(deltaX*deltaX + deltaY*deltaY);
}

void Point::print()
{
	cout << "Point at : ( " << x << " , " << y << " )" << endl;
}

