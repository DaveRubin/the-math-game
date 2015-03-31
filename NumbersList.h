#pragma once
#include "io_utils.h"
#include "Actor.h"
#include "Number.h"
#include <stdlib.h>     
#include <iostream>

using namespace std;
class NumbersList
{
	Number **numbers;
	int numChildren = 0;
	int listSize = 0;

public:

	void addNumber(Number*);
};

