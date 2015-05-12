#pragma once
class Operand
{
	char operandType;
public:
	Operand(char type = '+') : operandType(type) {};
	int calulate(int a, int b);
	bool isImprtant(){ return (operandType == '*' || operandType == '/'); };
	void setType(char type) { operandType = type; }
};

