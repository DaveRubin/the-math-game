#ifndef _EQUATION_H_
#define _EQUATION_H_

#pragma once
#include "io_utils.h"
#include "TextField.h"
#include <stdlib.h>     
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

class Equation :
	public TextField
{
	enum EQUATION_TYPE
	{
		ADD,MULTIPLY,SUBTRACT,DIVIDE
	};

	EQUATION_TYPE type = ADD;
	int difficulty = 0;
	int solution = 0;
	int level = 0;

	int getRandomElement();
public:

	void generateEquation();
	void generateEquation(EQUATION_TYPE);

	void setLevel(int input){ 
		level = input;
		generateEquation();
	}
	void levelUp(){ 
		level++; 
		generateEquation();
	}
	int getLevel(){ return level; };
	int getSolution(){ return solution; }

	Equation();
	~Equation();
};


#endif