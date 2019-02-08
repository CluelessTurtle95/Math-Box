#pragma once
#include"ExpTerm.h"

class Function
{
	vector<ExpTerm> expTerms;
public:
	Function();
	
	void addExpTerm(double coef, double exponent, Expression e);
	double eval(double x);
	void simplify();

	static Function to_func(Expression e);
};

