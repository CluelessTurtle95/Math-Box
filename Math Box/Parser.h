#pragma once
#include"Function.h"
#include"ExpParser.h"
#include"constants.h"

class Parser
{
	Function func;
	ExpParser simpleParser;
	string str;

	string searchParen();
public:
	Parser();

	void parse();
	void removeChar(char);
	Function getFunction();
	void setString(string str);
};

