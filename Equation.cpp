#include "Equation.h"

/*
try solution gets int 
if simple equation, then just compare to solution and return true or false
in simple mode, if true. set solved to true;

if 3 vars then check possible var for the first var,
if found possible , then add the number to the equation, and return true

set solved to true only if no vars remains
*/
bool Equation::trySolution(int input)
{
	//if one var, compare to solution
	if ((level >= 0) && (level < 21))
	{
		if (input == solution)
		{
			solved = true;
			return true;
		}
		else return false;
	}
	//if advanced
	else
	{
		//find first min
		int firstMin;
		if (minIndex2 == -1) firstMin = minIndex1;
		else firstMin = (minIndex1 < minIndex2) ? minIndex1 : minIndex2;

		//keep backup for the temp var
		int tmpElement = vars[firstMin];
		vars[firstMin] = input;

		//calcuate solution with the input as the first min 
		int tempSolution = calculateThree(minIndex2);
		//if possible, then set the the number to the input and return true
		if (tempSolution < level && tempSolution >= 0)
		{
			if (firstMin == minIndex1)
				minIndex1 = minIndex2;

			minIndex2 = -1;
			varCount--;

			printEquation();

			if (varCount == 0) solved = true;
			return true;
		}
		//if not, reset
		else
		{
			vars[firstMin] = tmpElement;
			return false;
		}
		
		//if vars == 1 then calculate solution,
		//if solution is the input then return true, and set to solved
		
	}
}

Equation::Equation()
{
	difficulty = 0;
	solution = 0;
	level = 0;
	type = ADD;
	solved = false;
	generateEquation(level);
}

/*
empty generateEquation draws a random equation type
and generate an equation suiting its current level
*/
void Equation::generateEquation(int equationLevel)
{
	solved = false;
	level = equationLevel;
	//get random equation type (0-3) for levels 1-20
	if ((level >= 0) && (level < 21))
	{
		elementsCount = 3;
		varCount = 1;
		Operand eqType;
		ops[0] = eqType;
		generateSingleEquation();
	}

	// build equation for level 21 and up
	else if (level >= 21)
	{
		elementsCount = 4;
		varCount = 2;
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

int Equation::calculateThree(int varIndex)
{
	//calcuate equation (n1,n2,n3 ,op1,op2 ,varIndex)
	//if varIndex = 4 then calculate n1-3 and return the result
	//check if var index have neighbor multiply/divide if so
	//ignore the neighbor\s and counter the non neighbor with relevant multiply\divide
	//check for regular nums and counter them (-+) with the solution
	//now return the solution
	Operand op1 = ops[0];
	Operand op2 = ops[1];

	int n1 = vars[0];
	int n2 = vars[1];
	int n3 = vars[2];
	int sol = vars[3];

	if (varIndex == 3)
	{
		//if the solution is missing, then just calculate the expression 
		//and return result
		int tempNum;

		//check if special order of action is needed
		if (!op1.isImprtant() && op2.isImprtant())
		{
			tempNum = op2.calulate(n2, n3);
			return op1.calulate(n1, tempNum);
		}
		else
		{
			tempNum = op1.calulate(n1, n2);
			return op2.calulate(tempNum, n3);
		}
	}

	else
	{
		switch (varIndex)
		{
		case 0:

			//case of n1 is the variable
			if (!op1.isImprtant() && op2.isImprtant())
			{
				int tempNum = op2.calulate(n2, n3);
				sol = op1.counterAction(sol, tempNum);
				return sol;
			}
			else
			{
				//counter 2 and result
				sol = op2.counterAction(sol, n3);
				//counter 1 and result
				sol = op1.counterAction(sol, n2);
				return sol;
			}
			break;

		case 1:

			/*case of n2 is the variable*/
			//get rid of n3
			sol = op2.counterAction(sol, n3);
			if (!op1.isImprtant()) n1 = op2.counterAction(n1, n3);

			//now get rid of n1
			// * or /
			if (op1.isImprtant())
			{
				//6/x = 5	=> x = 6/5
				if (op1.getOp() == '/')
					return op1.calulate(n1, sol);
				//6x = 5	=> x = 5/6
				else
					return op1.counterAction(sol , n1);
			}
			// + or -
			else
			{
				//6-x = 5	=> x = 6-5
				if (op1.getOp() == '-')
					return op1.calulate(n1, sol);
				//6+x = 5	=> x = 5-6
				else
					return op1.counterAction(sol, n1);
			}
			break;

		case 2:

			//case of n3 is the variable
			if (!op1.isImprtant() && op2.isImprtant())
			{
				Operand *minus = new Operand('-');
				//reduce n1 from solution
				sol = minus->calulate(sol, n1);
				//clean the var from n2
				sol = op2.counterAction(sol, n2);
				delete minus;
				//if op1 is minus, the invert solution before returning
				if (op1.getOp() == '-') sol *= -1;
				return sol;
			}
			else
			{
				//calculate first two
				int temp = op1.calulate(n1, n2);
				
				//then if op2 its * or / then switch between n3 and sol, and return calculation
				if (op2.isImprtant())
				{
					//if 6/x = 5 then x = 6/5
					if (op2.getOp() == '/')
					{
						return op2.calulate(temp, sol);
					}
					//if 6x = 5 then x= 5/6
					else
					{
						return op2.counterAction(sol, temp);
					}
				}
				//if op2 is + or -
				else
				{
					//16 - X = 10
					//-X = -6
					//return 6
					Operand switchSide = Operand('-');
					temp = switchSide.calulate(temp, sol);

					//then we need to switch the var to the other side of the equation
					if (op2.getOp() == '-') return temp;
					else return -temp;
				}
			}
			break;
		}
	}
	return 0;
}

//print out the equation ommitting the smallest solutions
void Equation::printEquation()
{
	stringstream sstm;
	string varChars[] = { to_string(vars[0]), to_string(vars[1]), to_string(vars[2]), to_string(vars[3])};

	if (minIndex1 != -1)
		varChars[minIndex1] = "__";
	if (minIndex2 != -1)
		varChars[minIndex2] = "__";

	sstm << varChars[0] << " " << ops[0].getOp() << " " << varChars[1] << " " << ops[1].getOp() << " " << varChars[2] << " " << '=' << " " << varChars[3] << endl;
	
	setText(sstm.str());
	
	//save solution
//	solution1 = vars[min1];
//	solution2 = vars[min2];
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
void Equation::generateSingleEquation()
{
	Operand operand = ops[0];
	int num1 = getRandomElement();
	int num2 = getRandomElement();
	int num3;
	char sign = ' ';

	if (operand.isReducing())
	{
		num3 = num1;
		num1 = operand.counterAction(num2, num3);
	}
	else
	{
		num3 = operand.calulate(num1, num2);
	}

	//parse the numbers into the output string
	stringstream sstm;
	sstm << num1 << operand.getOp() << "__" << "=" << num3;
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


	int tmpVars[] = { num1, num2, num3, solution };
	varCount = 2;

	vars[0] = num1;
	vars[1] = num2;
	vars[2] = num3;
	vars[3] = solution;

	ops[0] = Operand(op1);
	ops[1] = Operand(op2);

	getLowest(tmpVars, 4, min1, min2);

	minIndex1 = min1;
	minIndex2 = min2;

	printEquation();
	//TODO - generate solution for checking if X is a possible solution

}