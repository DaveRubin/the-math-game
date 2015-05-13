#include "Operand.h"

Operand::Operand(int type)
{
	switch (type)
	{
	case 0:
		operandType = '+';
		break;
	case 1:
		operandType = '*';
		break;
	case 2:
		operandType = '-';
		break;
	case 3:
		operandType = '/';
		break;
	}
}

int Operand::calulate(int a, int b)
{
	switch (operandType)
	{
	case '+' :
		return a + b;
	case '-' :
		return a - b;
	case '*' :
		return a * b;
	case '/' :
		return a / b;
	}
}

int Operand::counterAction(int a, int b)
{
	switch (operandType)
	{
	case '+':
		return a - b;
	case '-':
		return a + b;
	case '*':
		return a / b;
	case '/':
		return a * b;
	}
}

void Operand::setRandomOperand()
{
	int type = rand() % 4;

	switch (type)
	{
	case 0:
		operandType = '+';
		break;
	case 1:
		operandType = '-';
		break;
	case 2:
		operandType = '*';
		break;
	case 3:
		operandType = '/';
		break;
	}
}

//int calculateThree(int n1, int n2, int n3, int varIndex, Operand op1, Operand op2);

//bool Equation::possibleSollution(int num)
//{
//	//if we have 2 vars then we'll check if it possible to replace one of them
//	//set var X to be num
//	//then calculate the remaining var
//	//if in range, then possible
//	//if not move on to the next var
//	//if both vars are impossible then return false
//
//	//if we have only one var, then calculate the equation, if the numbers equals then true
//
//}
//
//int Equation::calculateThree(int n1, int n2, int n3, int varIndex, Operand op1, Operand op2)
//{
//	//calcuate equation (n1,n2,n3 ,op1,op2 ,varIndex)
//	//if varIndex = 4 then calculate n1-3 and return the result
//	if (varIndex == 4)
//	{
//		int tempNum;
//		if (!op1.isImprtant() && op2.isImprtant())
//		{
//			tempNum = op2.calulate(n2, n3);
//			return op1.calulate(n1, tempNum);
//		}
//		else
//		{
//			tempNum = op1.calulate(n1, n2);
//			return op2.calulate(tempNum, n3);
//		}
//	}
//	//if its not the solution
//	//check if var index have neighbor multiply/divide if so
//	//ignore the neighbor\s and counter the non neighbor with relevant multiply\divide
//	//check for regular nums and counter them (-+) with the solution
//	//now return the solution
//	return 0;
//}