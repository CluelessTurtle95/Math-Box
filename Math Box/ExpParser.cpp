#include "pch.h"
#include "ExpParser.h"
#include"constants.h"
#include"Expression.h"

ExpParser::ExpParser()
{
}

void ExpParser::parse()
{
	expression = Expression();
	int plus_pos, minus_pos, min_pos, x_pos, max_pos = 1, exp_pos;

	double coef, exponent;
	// Erase Spaces
	// str.erase(remove(str.begin(), str.end(), ' '), str.end());

	while (max_pos != string::npos)
	{
		plus_pos = str.find("+");
		if (plus_pos != string::npos)
			if (plus_pos == 0)
				plus_pos = str.find("+", 1);

		minus_pos = str.find("-");
		if (minus_pos != string::npos)
			if (minus_pos == 0)
				minus_pos = str.find("-", 1);

		min_pos = minus_pos > plus_pos ? plus_pos : minus_pos;
		max_pos = minus_pos > plus_pos ? minus_pos : plus_pos;

		if (min_pos == string::npos)
			min_pos = max_pos;

		string token = str.substr(0, min_pos);
		if (min_pos != string::npos)
			str = str.substr(min_pos);

		exp_pos = token.find("^");
		x_pos = token.find("x");
		coef = stod(token.substr(0, exp_pos));
		if (exp_pos != string::npos)
			exponent = stod(token.substr(exp_pos + 1));
		else if (x_pos != string::npos)
			exponent = 1;
		else
			exponent = 0;

		expression.addTerm(coef, exponent);
	}
}

Expression ExpParser::getExpression()
{
	return expression;
}

void ExpParser::setString(string str)
{
	ExpParser::str = str;
}



