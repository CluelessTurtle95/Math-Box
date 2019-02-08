#include "pch.h"
#include "ExpTerm.h"
#include<cmath>

ExpTerm::ExpTerm()
{
}

void ExpTerm::setExpression(Expression e)
{
	ExpTerm::e = e;
}

Expression ExpTerm::getExpression()
{
	return e;
}

double ExpTerm::eval(double x)
{
	return coef * pow(e.evalFunc(x), exponent);
}
