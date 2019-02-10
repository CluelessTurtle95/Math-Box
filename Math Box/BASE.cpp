#include "pch.h"
#include "BASE.h"
#include<string>
#include<vector>
void Base::setCombo(string func1, string func2)
{
	combo = true;
	comboFunc1 = func1;
	comboFunc2 = func2;
}
Base::Base(std::string base)
{
	combo = false;
	baseFunc = base;	
}

Base::Base()
{
	combo = false;
	baseFunc = "x";
}
double Base::eval(double x)

{
	if (!combo)
	{
		if (baseFunc == "sin")
			return sin(x);
		if (baseFunc == "cos")
			return cos(x);
		if (baseFunc == "tan")
			return tan(x);
		if (baseFunc == "log")
			return log(x);
		if (baseFunc == "log10")
			return log10(x);
		if (baseFunc == "exp")
			return exp(x);
		if (baseFunc == "sqrt")
			return sqrt(x);
		if (baseFunc == "x")
			return x;
	}
	else
	{
		Base * temp = new Base(comboFunc1);
		double val = temp->eval(x);
		temp = new Base(comboFunc2);
		val *= temp->eval(x);
		delete temp;
		return val;
	}
}
Base Base::combine(Base a, Base b)
{
	Base temp;
	if (a.baseFunc == b.baseFunc)
		temp.baseFunc = a.baseFunc;
	else
	{
		temp.setCombo(a.baseFunc , b.baseFunc);
		temp.baseFunc = a.baseFunc + "*" + b.baseFunc;
	}
	return temp;
}
std::vector<std::string> Base::globalBaseList = {"sin","cos","tan","log","log10","exp","sqrt","x"};
//std::string Base::globalBase = "x";
