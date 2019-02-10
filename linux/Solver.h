#pragma once
#include "Function.h"
#include "Differentiator.h"
class Solver
{
	Function* function;
	Differentiator diff;
public:
	Solver();
	
	void fit(Function *);
	double eval(double guess);
	double newtonUpdate(double x);
};

