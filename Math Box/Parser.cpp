#include "pch.h"
#include "Parser.h"


string Parser::searchParen()
{
	int openPos = str.find("(");
	int closePos = str.find(")");

	if (openPos == string::npos || closePos == string::npos)
		return InvalidStr;

	return str.substr(openPos +1 , closePos - openPos );
}

Parser::Parser()
{
	func = Function();
	str = string();
	simpleParser = ExpParser();
}

void Parser::parse()
{
	removeChar(' ');
	if (str.find("(") != string::npos)
	{
		int openPos , closePos;
		string temp = searchParen();
		int expPos = str.find(")^");
		if (expPos != string::npos)
		{
			while(str.find("(") != string::npos)
			{
				int tempInt;
				openPos = str.find("(");
				closePos = str.find(")");
				if (openPos == string::npos)
					break;

				simpleParser.setString(searchParen());
				simpleParser.parse();
				string token = str;
				if (str.find("(", str.find("(") +1) != string::npos)
				{
					string temp;
					temp = str.substr(str.find(")"), str.find("(", 1 + str.find("(")) - str.find(")") + 1);
					tempInt = temp.find("+");

					if (tempInt == string::npos)
						tempInt = temp.find("-");
					if (tempInt == string::npos)
						tempInt = str.size() - str.find(")");
					tempInt = str.find(")") + tempInt;

					token = str.substr(0, tempInt);
					str = str.substr(tempInt);
				}
				else
				{
					str = string();
				}
				//cout << str;
				int coef = stod(token.substr(0, openPos+1));
				int exponent = stod(token.substr(closePos + 2));
				//cout << coef << exponent;
				func.addExpTerm(coef, exponent, simpleParser.getExpression());
			}
		}
		else
		{

		}
		
	}
	else
	{
		simpleParser.setString(str);
		simpleParser.parse();
		func = Function::to_func(simpleParser.getExpression());
	}
}

void Parser::removeChar(char ch)
{
	string result;
	for (size_t i = 0; i < str.size(); i++)
	{
		char currentChar = str[i];
		if (currentChar != ch)
			result += currentChar;
	}
	str = result;
}

Function Parser::getFunction()
{
	return func;
}

void Parser::setString(string str)
{
	Parser::str = str;
}