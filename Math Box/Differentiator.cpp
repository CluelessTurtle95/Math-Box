#include "pch.h"
#include "Differentiator.h"


Differentiator::Differentiator()
{
}

void Differentiator::fit(Function * function, double delX)
{
	Differentiator::function = function;
	Differentiator::delX = delX;
}

double Differentiator::eval(double x)
{
	double y;

	y = (function->eval(x + delX) - function->eval(x - delX)) / (2*delX);

	return y;
}