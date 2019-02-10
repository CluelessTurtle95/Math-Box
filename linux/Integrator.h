#pragma once
#include "Function.h"
#include "constants.h"


class Integrator
{
	double y;
	Function* function;
	approximation type;

public:
	Integrator();

	void fit(Function *function, approximation app);
	double eval(double left, double right, int n);
	double modify();
};

