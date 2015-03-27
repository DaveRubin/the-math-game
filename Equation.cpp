#include "Equation.h"

Equation::Equation()
{
	generateEquation();
}

/*
empty generateEquation draws a random equation type
and generate an equation suiting its current level
*/
void Equation::generateEquation()
{
	//generate identified seed for rand
	srand(time(NULL));
	//get random equation type (0-3)
	EQUATION_TYPE  eqType = 
		static_cast<EQUATION_TYPE>(rand() % 4);
	generateEquation(eqType);
}

/*
get random element for the equation according to its level
*/
int Equation::getRandomElement()
{
	srand(time(NULL));
	int randomSeed = rand();
	return (randomSeed % 10 + 1 + level);
}

/*
generateEquation gets an equation type
and generate an equation suiting its current level

input 
	eqType(EQUATION_TYPE) - the euqation type 
sets
	text(string) - to hold the euqation for print
	solution(int) - the solution to the current equation
*/
void Equation::generateEquation(Equation::EQUATION_TYPE eqType)
{
	int num1 = getRandomElement();
	int num2 = getRandomElement();
	int num3;
	char sign = ' ';

	switch (eqType)
	{
	case Equation::ADD:
		sign = '+';
		num3 = num1 + num2;
		break;
	case Equation::MULTIPLY:
		sign = '*';
		num3 = num1 * num2;
		break;
	case Equation::SUBTRACT:
		sign = '-';
		num3 = num1;
		num1 = num2 + num3;
		break;
	case Equation::DIVIDE:
		sign = '/';
		num3 = num1;
		num1 = num2 * num3;
		break;
	default:
		break;
	}

	//parse the numbers into the output string
	stringstream sstm;
	sstm << num1 << sign << "__" << "=" << num3;
	setText(sstm.str());
	//save solution
	solution = num2;

	//print for debugging 
	//cout << outputText << " (" << solution << ")" << endl;
}