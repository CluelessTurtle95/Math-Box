#include "pch.h"
#include "Function.h"
#include<ctype.h>
#include"constants.h"

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
	vector<ExpTerm> result;
	cout << "\n Simplifying \n";
	for (ExpTerm expTerm : expTerms)
	{	
		if (expTerm.getExp() == (int)expTerm.getExp() && expTerm.getExp() > 0)
		{
			Expression temp,temp2;
			temp = expTerm.getExpression();
			temp2 = temp;
			for (int i = 1; i < expTerm.getExp(); i++)
				temp = Expression::multiply(temp2, temp);
			temp.scalar(expTerm.getCoef());
			temp.simplify();
			expTerm.setExpression(temp);
			expTerm.setCoef(1);
			expTerm.setExp(1);
		}
		result.push_back(expTerm);
	}
	expTerms = result;
}

string Function::getString()
{
	string result = string();
	for (ExpTerm expterm : expTerms)
	{
		if (expterm.getCoef() > 0)
			result += "+";

		result += ( clean(to_string(expterm.getCoef())) + "(" + expterm.getExpression().getString() + ")^" + clean(to_string(expterm.getExp())) + " ");
	}

	return result;
}

Function Function::to_func(Expression e)
{
	Function temp;
	temp.addExpTerm(1, 1, e);
	return temp;
}

string Function::clean(string val)
{
	while (val[val.size() - 1] == '0')
		val = val.substr(0, val.size() - 1);
	return val;
}