#include "pch.h"
#include "Term.h"
#include<cmath>
#include"constants.h"

Term::Term()
{
	coef = InvalidValue;
	exponent = InvalidValue;
}

double Term::eval(double x)
{
	return coef * pow(x, exponent);
}

double Term::getCoef()
{
	return coef;
}

double Term::getExp()
{
	return exponent;
}

void Term::setCoef(double val)
{
	coef = val;
}

void Term::setExp(double val)
{
	exponent = val;
}

Term Term::Add(Term a, Term b)
{
	Term result;
	if (a.exponent == b.exponent)
	{
		result.coef = a.coef + b.coef;
		result.exponent = a.exponent;
	}
	return result;
}

Term Term::Multiply(Term a, Term b)
{
	Term result;
	result.exponent = a.exponent + b.exponent;
	result.coef = a.coef*b.coef;
	return result;
}