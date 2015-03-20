#include "Equation.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include <sstream>

Equation::Equation()
{
	generateEquation();
}


Equation::~Equation()
{

}

void Equation::generateEquation()
{
	//generate identified seed for rand
	srand(time(NULL));
	//get random equation type (0-3)
	EQUATION_TYPE  eqType = 
		static_cast<EQUATION_TYPE>(rand() % 4);
	generateEquation(eqType);
}

int Equation::getRandomElement()
{
	return (rand() % 10 + 1 + level) ;
}

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
		num3 = generateAdd(num1, num2);
		break;
	case Equation::MULTIPLY:
		sign = '*';
		num3 = generateMultiply(num1, num2);
		break;
	case Equation::SUBTRACT:
		sign = '-';
		num3 = num1;
		num1 = generateAdd(num2, num3);
		break;
	case Equation::DIVIDE:
		sign = '/';
		num3 = num1;
		num1 = generateMultiply(num2, num3);
		break;
	default:
		break;
	}

	//parse the numbers into the output string
	stringstream sstm;
	sstm << num1 << sign << "__" << "=" << num3;
	outputText = sstm.str();
	//save solution
	solution = num2;

	//print for debugging 
	cout << outputText << " (" << solution << ")" << endl;
}

int Equation::generateAdd(int num1, int num2)
{
	return num1 + num2;
}
int Equation::generateMultiply(int num1, int num2)
{
	return num1 * num2;
}

