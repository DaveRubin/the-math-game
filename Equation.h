#ifndef _EQUATION_H_
#define _EQUATION_H_

#pragma once
#include "io_utils.h"
#include "TextField.h"
#include <stdlib.h>     
#include <ctime>
#include <sstream>
#include <iostream>
#include <list>

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
	int solution1;	//for level 21 and up when there are two solutions...
	int solution2;	//for level 21 and up when there are two solutions...
	int level;

	int getRandomElement();
	int getRandomElementInRange(int low = 1, int high = 21);		//get random number in range between (and including) low limit and high
	void getLowest(int * vars, int & i, int & j);		//get the two smallest variables' indices

	//randomizer for keeping divided numbers as integers that are in range
	int dividerRandomElements(int & numerator, int & denominator, int low = 0, int high = 21);
	
	void printEquation(int * vars, int len, int i, int j);		//function to print out equation

	/*
	list<int> vars;					//list of the solutions
	list <EQUATION_TYPE> opers;		//list of the operands
	*/
	

public:

	void generateEquation();
	void generateEquation(EQUATION_TYPE);						//generates equations for levels 1 - 20
	void generateEquation21(EQUATION_TYPE, EQUATION_TYPE);		//generates equations for levels 21 - 40


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
	int getSolution1(){ return solution1; }
	int getSolution2(){ return solution2; }

	Equation();
	~Equation();
};


#endif