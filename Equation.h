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

	void setLevel(int);
	void levelUp();

	void render();

	int getLevel();
	Equation();
	~Equation();
};

