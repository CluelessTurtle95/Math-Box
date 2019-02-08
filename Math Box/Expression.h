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
	string getString();
	double evalFunc(double x);
	vector<Term> getTerms();

	static vector<Term> multiply(Expression, Expression);
};

