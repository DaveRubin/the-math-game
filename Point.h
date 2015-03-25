#pragma once
#include <stdlib.h>  
#include <iostream>

using namespace std;

class Point
{
	int x;
	int y;
public:
	Point() :x(0), y(0){};
	Point(int x, int y);
	~Point();
	int getX();
	int getY();
	float distance(Point p);
	void add(Point p);
	void multiply(Point p);
	void set(int x, int y);
	void set(Point p);
	void print();
};

