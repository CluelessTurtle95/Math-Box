
#include "Expression.h"
#include "constants.h"
#include<string>
#include"BASE.h"

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

void Expression::addTerm(double coef, double exp , string base)
{
	Term* temp = new Term();
	temp->setCoef(coef);
	temp->setExp(exp);
	temp->termBase.baseFunc = base;
	terms.push_back(*temp);
	delete temp;
}

void Expression::addTerm(Term t)
{
	terms.push_back(t);
}

vector<Term> Expression::getTerms()
{
	return terms;
}

Expression Expression::multiply(Expression a, Expression b)
{
	Expression result;
	for (unsigned int i = 0; i < a.getTerms().size(); i++)
		for (unsigned int j = 0; j < b.getTerms().size(); j++)
			result.addTerm(Term::Multiply(a.getTerms()[i], b.getTerms()[j]));
	return result;
}

string Expression::getString()
{
	string result = "";
	for (unsigned int i = 0; i < terms.size(); i++)
	{
		if (terms[i].getExp() == 0)
			result += clean(to_string(terms[i].getCoef())) ;
		else if (terms[i].getExp() == 1)
			result += (clean(to_string(terms[i].getCoef())) + terms[i].termBase.baseFunc );
		else
			result += (clean(to_string(terms[i].getCoef())) + terms[i].termBase.baseFunc + "^" + clean(to_string(terms[i].getExp())));
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

void Expression::scalar(double val)
{
	vector<Term> result;
	for (Term term : terms)
	{
		term.setCoef(val * term.getCoef());
		result.push_back(term);
	}
	terms = result;
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

string Expression::clean(string val)
{
	while (val[val.size() - 1] == '0')
		val = val.substr(0, val.size() - 1);
	return val;
}
