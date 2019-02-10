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
	static string removeChar(string ,char);
	Function getFunction();
	void setString(string str);
};

