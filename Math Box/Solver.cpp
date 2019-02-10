#include "pch.h"
#include "Solver.h"
#include "constants.h"

Solver::Solver()
{
}

void Solver::fit(Function * function)
{
	Solver::function = function;
	diff.fit(function , DiffDelX);
}

double Solver::eval(double guess = 10)
{
	double current = newtonUpdate(guess), last;
	int counter = 0;
	bool success = true;
	do
	{
		counter++;
		last = guess;
		guess = guess - (1)*newtonUpdate(guess);
		current = guess;
		if (counter > MaxSolveCounter)
		{
			success = false;
			break;
		}
	} while (fabs(current / last - 1) > 0.00000001);

	cout << counter << " Iterations \n";
	if (!success)
	{
		cout << "No Convergence! Current step x = " << guess;
		return InvalidValue;
	}
	return guess;
}

double Solver::newtonUpdate(double x)
{
	return function->eval(x)/diff.eval(x);
}


