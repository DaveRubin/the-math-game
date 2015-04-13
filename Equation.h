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

	EQUATION_TYPE type;
	int difficulty;
	int solution;
	int level;

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