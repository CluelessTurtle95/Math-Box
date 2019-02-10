
#include "Integrator.h"

Integrator::Integrator()
{
	y = 0;
}

void Integrator::fit(Function *function, approximation app = Left)
{
	this->function = function;
	type = app;
}

double Integrator::eval(double left, double right, int n)
{
	double result;

	double del_x = (right - left) / n;
	result = 0;
	for (int i = 0; i < n; i++)
	{
		y = function->eval(left + (i + modify())*del_x);
		result += y * del_x;
	}

	return result;
}

double Integrator::modify()
{
	switch (type)
	{
	case Left:
		return 0;
		break;
	case Right:
		return 1;
		break;
	case Mid:
		return 0.5;
		break;
	default :
		return (double)InvalidValue;
		break;
	}
}
