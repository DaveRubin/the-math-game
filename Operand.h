#pragma once
#include <stdlib.h>     

class Operand
{
	char operandType;
public:
	Operand(char type) : operandType(type) {};
	Operand(int type);
	Operand() { setRandomOperand(); };
	int calulate(int a, int b);
	int counterAction(int a, int b);

	void setType(char type) { operandType = type; }
	void setRandomOperand();

	bool isImprtant(){ return (operandType == '*' || operandType == '/'); };
	bool isReducing(){ return (operandType == '-' || operandType == '/'); };
	char getOp() { return operandType; }
};

