#pragma once
#include"Base.h"

class Term
{
protected:
	double coef;
	double exponent;
public:

	BASE termBase;

	Term();
	double eval(double x);
	double getCoef();
	double getExp();
	void setCoef(double val);
	void setExp(double val);
	
	static Term Add(Term a, Term b);
	static Term Multiply(Term a, Term b);
};

