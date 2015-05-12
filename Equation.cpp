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

//get the two smallest variables' indices
void Equation::getLowest(int * vars, int len, int & min1, int & min2)
{
	int tmp1, tmp2;
	int ind1 = 0, ind2 = 0;
	tmp1 = tmp2 = INT_MAX;
	for (int k = 0; k < len; k++)
	{
		if (tmp1 > vars[k])
		{
			tmp2 = tmp1;
			tmp1 = vars[k];
			ind1 = k;
		}
		// if vars[k] is in between min1 and min2 then update min2, I am assuming that there is a second smallest var
		else if (tmp2 > vars[k] && vars[k] != tmp1)
		{
			tmp2 = vars[k];
			ind2 = k;
		}
	}
	min1 = ind1;
	min2 = ind2;
}

//print out the equation ommitting the smallest solutions
void Equation::printEquation(int * vars, int len, char operand1, char operand2, int min1, int min2)
{
	stringstream sstm;
	string varChars[] = { to_string(vars[0]), to_string(vars[1]), to_string(vars[2]), to_string(vars[3])};
	varChars[min1] = "__";
	if (min2 != -1)
		varChars[min2] = "__";

	sstm << varChars[0] << " " << operand1 << " " << varChars[1] << " " << operand2 << " " << varChars[2] << " " << '=' << " " << varChars[3] << endl;
	
	setText(sstm.str());
	
	//save solution
	solution1 = vars[min1];
	solution2 = vars[min2];
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
	int high, low, divided;						//for calculation and building the equation
	int min1, min2;								//indices for smallest vars
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

	int vars[] = { num1, num2, num3, solution };
	Equation::getLowest(vars, 4, min1, min2);
	Equation::printEquation(vars, 4, operand1, operand2, min1, min2);
	//TODO - generate solution for checking if X is a possible solution
}