#include "Point.h"


Point::Point(int inputX, int inputY)
{
	x = inputX;
	y = inputY;
}


Point::~Point()
{
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

void Point::set(int inputX, int inputY)
{
	x = inputX;
	y = inputY;
}

void Point::set(Point p)
{
	x = p.getX();
	y = p.getY();
}

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


void Point::add(Point p)
{
	x += p.getX();
	y += p.getY();
}
void Point::multiply(Point p)
{
	x *= p.getX();
	y *= p.getY();
}