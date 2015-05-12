#include "Equation.h"

Equation::Equation()
{
	difficulty = 0;
	solution = 0;
	level = 0;
	type = ADD;
	generateEquation();
}

/*
empty generateEquation draws a random equation type
and generate an equation suiting its current level
*/
void Equation::generateEquation()
{
	//get random equation type (0-3) for levels 1-20
	if ((level >= 0) && (level < 21))
	{
		EQUATION_TYPE  eqType =
			static_cast<EQUATION_TYPE>(rand() % 4);
		generateEquation(eqType);
	}

	// build equation for level 21 and up
	else if (level >= 21)
	{
		EQUATION_TYPE op1 = static_cast<EQUATION_TYPE>(rand() % 4);
		EQUATION_TYPE op2 = static_cast<EQUATION_TYPE>(rand() % 4);
		generateEquation21(op1, op2);
	}
	
}

/*
get random element for the equation according to its level
*/
int Equation::getRandomElement()
{
	int randomSeed = rand();
	return (randomSeed % 10 + 1 + level);
}


//get random element in range
int Equation::getRandomElementInRange(int low, int high)
{
	return (rand() % (high - low) + low);
}


//randomizer for keeping divided numbers as integers that are in range
int Equation::dividerRandomElements(int & numerator, int & denominator, int low, int high)
{
	int divSolution = Equation::getRandomElementInRange(low,high);		//randomly select solution for div segment in equation
	denominator = rand() % 21;											//randomly select int for denominator
	numerator = divSolution * denominator;								//solve for selected to find numerator

	return divSolution;
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
}



void Equation::generateEquation21(Equation::EQUATION_TYPE op1, Equation::EQUATION_TYPE op2)
{
	int num1, num2, num3, solution = 0;			//initialize the soltuion and variables
	int high, low, divided;
	char operand1 = ' ', operand2 = ' ';

	switch (op1)
	{
	case Equation::ADD:
		operand1 = '+';
		switch (op2)
		{
		case Equation::ADD:
			operand2 = '+';
			num1 = Equation::getRandomElementInRange();
			num2 = Equation::getRandomElementInRange();
			num3 = Equation::getRandomElementInRange();
			solution = num1 + num2 + num3;
			break;

		case Equation::MULTIPLY:
			operand2 = '*';
			num1 = Equation::getRandomElementInRange();
			num2 = Equation::getRandomElementInRange();
			num3 = Equation::getRandomElementInRange();
			solution = num1 + num2 * num3;
			break;

		case Equation::SUBTRACT:
			operand2 = '-';
			num1 = Equation::getRandomElementInRange();
			num2 = Equation::getRandomElementInRange();
			num3 = Equation::getRandomElementInRange(1, num1 + num2 - 1);
			solution = num1 + num2 - num3;
			break;

		case Equation::DIVIDE:
			operand2 = '/';
			Equation::dividerRandomElements(num2, num3);
			num1 = Equation::getRandomElementInRange();
			solution = num1 + num2 / num3;
			break;
		}
		break;

	case Equation::MULTIPLY:
		operand1 = '*';
		switch (op2)
		{
		case Equation::ADD:
			operand2 = '+';
			num1 = Equation::getRandomElementInRange();
			num2 = Equation::getRandomElementInRange();
			num3 = Equation::getRandomElementInRange();
			solution = num1 * num2 + num3;
			break;

		case Equation::MULTIPLY:
			operand2 = '*';
			num1 = Equation::getRandomElementInRange();
			num2 = Equation::getRandomElementInRange();
			num3 = Equation::getRandomElementInRange();
			solution = num1 * num2 * num3;
			break;

		case Equation::SUBTRACT:
			operand2 = '-';
			num1 = Equation::getRandomElementInRange();
			num2 = Equation::getRandomElementInRange();
			high = num1 * num2 - 1;
			if (high < 21)								//avoiding negative or zero solution
			{
				num3 = Equation::getRandomElementInRange(1,high);	
			}
			else
				num3 = Equation::getRandomElementInRange();

			solution = num1 * num2 - num3;
			break;

		case Equation::DIVIDE:
			operand2 = '/';
			Equation::dividerRandomElements(num2, num3);
			num1 = Equation::getRandomElementInRange();
			solution = num1 * num2 / num3;
			break;
		}
		break;

	case Equation::SUBTRACT:
		operand1 = '-';
		switch (op2)
		{
		case Equation::ADD:
			operand2 = '+';
			num1 = Equation::getRandomElementInRange();
			num2 = Equation::getRandomElementInRange();
			num3 = Equation::getRandomElementInRange(abs(num1 - num2) + 1, 21);
			solution = num1 - num2 + num3;
			break;

		case Equation::MULTIPLY:
			operand2 = '*';
			num2 = Equation::getRandomElementInRange();
			num3 = Equation::getRandomElementInRange();
			low = num2 * num3 + 1;
			num1 = Equation::getRandomElementInRange(low, 10000);
			solution = num1 - num2 * num3;
			break;

		case Equation::SUBTRACT:
			operand2 = '-';
			num1 = Equation::getRandomElementInRange(3, 21);
			num2 = Equation::getRandomElementInRange(1, (num1 - 2));
			num3 = Equation::getRandomElementInRange(1, (num1 - num2 - 1));
			solution = num1 - num2 - num3;
			break;

		case Equation::DIVIDE:
			operand2 = '/';
			low = Equation::dividerRandomElements(num2, num3) + 1;
			num1 = Equation::getRandomElementInRange(low, 10000);
			solution = num1 - num2 / num3;
			break;
		}
		break;

	case Equation::DIVIDE:
		operand1 = '/';
		switch (op2)
		{
		case Equation::ADD:
			operand2 = '+';
			dividerRandomElements(num1, num2);
			num3 = Equation::getRandomElementInRange();
			solution = num1 / num2 + num3;
			break;

		case Equation::MULTIPLY:
			operand2 = '*';
			dividerRandomElements(num1, num2);
			num3 = Equation::getRandomElementInRange();
			solution = num1 / num2 * num3;
			break;

		case Equation::SUBTRACT:
			operand2 = '-';
			divided = dividerRandomElements(num1, num2);
			if (divided < 21)
			{
				num3 = Equation::getRandomElementInRange(1, divided - 1);;	//solution must be positive
			}
			else
				num3 = Equation::getRandomElementInRange();					//no restrictions

			solution = num1 / num2 - num3;
			break;

		case Equation::DIVIDE:
			operand2 = '/';
			solution = Equation::getRandomElementInRange();
			num2 = Equation::getRandomElementInRange();
			num1 = Equation::getRandomElementInRange() * num2 * solution;
			num3 = num1 / num2 / solution;
			break;
		}
		break;
	}
	//TODO - build equation
	//TODO - find two smallest variables
	//TODO - generate solution for checking if X is a possible solution
}