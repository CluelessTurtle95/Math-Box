#pragma once
#include"Term.h"
#include"Expression.h"

class ExpTerm : public Term
{
	Expression e;
public:
	ExpTerm();

	void setExpression(Expression e);

	Expression getExpression();

	double eval(double x);
};

