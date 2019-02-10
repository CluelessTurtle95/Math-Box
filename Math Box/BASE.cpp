#include "pch.h"
#include "BASE.h"
#include<string>
#include<vector>
BASE::BASE(std::string base)
{
	baseFunc = base;	
}

BASE::BASE()
{
	baseFunc = "x";
}
double BASE::eval(double x)
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
std::vector<std::string> BASE::globalBaseList = {"sin","cos","tan","log","log10","exp","sqrt","x"};
//std::string BASE::globalBase = "x";
