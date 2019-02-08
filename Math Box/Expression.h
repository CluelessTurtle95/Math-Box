#pragma once
#include<iostream>
#include<vector>
#include"Term.h"
#include<string>

using namespace std;

class Expression
{
	vector<Term> terms;
public:
	Expression();
	void simplify();
	void addTerm(double coef, double exp);
	void addTerm(Term t);
	string getString();
	void scalar(double val);
	double evalFunc(double x);
	string clean(string val);
	vector<Term> getTerms();

	static Expression multiply(Expression, Expression);
};

