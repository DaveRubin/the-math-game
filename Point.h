#ifndef _POINT_H_
#define _POINT_H_

#include <stdlib.h>  
#include <iostream>

using namespace std;

class Point
{
	int x;
	int y;
public:
	Point() :x(0), y(0){};
	Point(int inX, int inY){
		x = inX;
		y = inY;
	}

	int getX() { return x; }
	int getY() { return y; }

	void add(Point p){
		x += p.x;
		y += p.y;
	}

	void multiply(Point p){
		x *= p.x;
		y *= p.y;
	}

	void set(int inX, int inY){
		x = inX;
		y = inY;
	}
	void set(Point p){
		x = p.x;
		y = p.y;
	}

	void print();
	bool equels(Point p){
		return (p.x == x && p.y == y);
	}
	float distance(Point p);
};


#endif