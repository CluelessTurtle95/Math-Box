#pragma once
#include<string>
#include"Expression.h"

using namespace std;

class ExpParser
{
	string str;
	Expression expression;
public:
	ExpParser();

	void setString(string str);
	void parse();
	Expression getExpression();
};

