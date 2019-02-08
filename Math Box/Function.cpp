#include "pch.h"
#include "Function.h"
#include<ctype.h>

Function::Function()
{
	expTerms.empty();
}

void Function::addExpTerm(double coef, double exponent, Expression e)
{
	ExpTerm * temp = new ExpTerm();
	temp->setExp(exponent);
	temp->setExpression(e);
	temp->setCoef(coef);
	expTerms.push_back(*temp);
	delete temp;
}

double Function::eval(double x)
{
	double result = 0;
	for (ExpTerm term : expTerms)
	{
		result += term.eval(x);
	}
	return result;
}

void Function::simplify()
{
	for (ExpTerm expTerm : expTerms)
	{	
		if (isdigit(expTerm.getExp()) && expTerm.getExp() > 0)
		{
			Expression temp;
			temp = expTerm.getExpression();

			for (int i = 1; i < expTerm.getExp(); i++)
				temp = Expression::multiply(temp, temp);

			temp.scalar(expTerm.getCoef());
			temp.simplify();
			expTerm.setExpression(temp);
			expTerm.setCoef(1);
			expTerm.setExp(1);
		}
	}
}

Function Function::to_func(Expression e)
{
	Function temp;
	temp.addExpTerm(1, 1, e);
	return temp;
}
