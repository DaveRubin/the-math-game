#include "Point.h"

float Point::distance(Point p)
{
	//preperation for next ex
	/*int deltaX = abs(p.getX() - x );
	int deltaY = abs( p.getY() - y);
	return sqrt(deltaX*deltaX + deltaY*deltaY);*/
	return 0;
}

void Point::warp()
{

	//check out of bounds
	if (x >= SCREEN_WIDTH) 
		x = x % SCREEN_WIDTH;

	else if (x < 0)
	{
		while (x < 0)
			x += SCREEN_WIDTH;
	}

	if (y >= SCREEN_HEIGHT)
		y = y % SCREEN_HEIGHT + HUD_HEIGHT;

	else if (y < HUD_HEIGHT)
	{
		while (y < HUD_HEIGHT)
			y += STAGE_HEIGHT;
	}
}

bool Point::isOutOfBounds()
{
	return (y < HUD_HEIGHT || y >= SCREEN_HEIGHT || x < 0 || x >= SCREEN_WIDTH);
}

void Point::print()
{
	cout << "Point at : ( " << x << " , " << y << " )" << endl;
}