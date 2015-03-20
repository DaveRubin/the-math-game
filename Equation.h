#pragma once
#include "io_utils.h"
#include <iostream>

using namespace std;

//TODO: extend textfiels
class Equation
{
	enum EQUATION_TYPE
	{
		ADD,MULTIPLY,SUBTRACT,DIVIDE
	};
	EQUATION_TYPE type = ADD;
	string outputText = "";
	int difficulty = 0;
	int solution = 0;
	int level = 0;
	//helper function for equation generation
	//the functions will get 2 numbers and return the missing one 
	//the second in add\multiply, and the first in divide\ subtract
	int generateAdd		(int num1, int num2);
	int generateMultiply(int num1, int num2);

	int getRandomElement();

public:
	void generateEquation();
	void generateEquation(EQUATION_TYPE);
	Equation();
	~Equation();
};

