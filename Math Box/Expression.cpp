#include "pch.h"
#include "Expression.h"
#include "constants.h"
#include<string>

Expression::Expression()
{
	terms.empty();
}

void Expression::simplify()
{
	vector<Term> result;
	int n = terms.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				Term temp;
				temp = Term::Add(terms[i], terms[j]);
				if (temp.getCoef() != InvalidValue && temp.getExp() != InvalidValue)
				{
					terms[i] = temp;
					terms[j].setCoef(0);
					terms[j].setExp(0);
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (terms[i].getCoef() != 0)
			result.push_back(terms[i]);
	}
	terms = result;
}

void Expression::addTerm(double coef, double exp)
{
	Term* temp = new Term();
	temp->setCoef(coef);
	temp->setExp(exp);
	terms.push_back(*temp);
	delete temp;
}

vector<Term> Expression::getTerms()
{
	return terms;
}

vector<Term> Expression::multiply(Expression a, Expression b)
{
	vector<Term> result;
	for (int i = 0; i < a.getTerms().size(); i++)
		for (int j = 0; j < b.getTerms().size(); j++)
			result.push_back(Term::Multiply(a.getTerms()[i], b.getTerms()[j]));
	return result;
}

string Expression::getString()
{
	string result = "";
	for (int i = 0; i < terms.size(); i++)
	{
		if (terms[i].getExp() == 0)
			result += to_string(terms[i].getCoef()) ;
		else if (terms[i].getExp() == 1)
			result += (to_string(terms[i].getCoef()) + "x");
		else
			result += (to_string(terms[i].getCoef()) + "x^" + to_string(terms[i].getExp()));
		if (i < terms.size() - 1)
		{
			if (terms[i + 1].getCoef() > 0)
				result += " +";
			else
				result += " ";
		}
	}
	return result;
}

double Expression::evalFunc(double x)
{
	double result = 0;
	for (Term term : terms)
	{
		result += term.eval(x);
	}
	return result;
}
