#pragma once
#include "Function.h"

class Differentiator
{
	Function* function;
	double delX;

public:
	Differentiator();
	void fit(Function *, double delX );

	double eval(double x);
};

