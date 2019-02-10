#include "pch.h"
#include "ExpParser.h"
#include"constants.h"
#include"Expression.h"
#include "constants.h"
#include "BASE.h"
#include<vector>
using namespace std;

ExpParser::ExpParser()
{
}

void ExpParser::parse()
{
	vector<int> baseSearch;
	for (string baseStr : BASE::globalBaseList )
	{
		while (str.find("+" + baseStr) != string::npos)
			str.replace(str.find("+" + baseStr), 1 + baseStr.length(), "+1" + baseStr);
		while (str.find("-" + baseStr) != string::npos)
			str.replace(str.find("-" + baseStr), 1 + baseStr.length(), "-1" + baseStr);
	}

	int first = 0;
	string base;
	

//	int first = 0, index = 0;
//	vector<string> baseList;
//	bool flag = true;
//	while (flag)
//	{
//		flag = false;
//		for (int i = 0; i < baseSearch.size(); i++)
//		{
//			if (baseSearch[i] != string::npos)
//				if (baseSearch[i] <= first)
//				{
//					first = baseSearch[i];
//					index = i;
//					flag = true;
//				}
//		}
//		if (flag)
//		{
//			baseList.push_back(BASE::globalBaseList[index]);
//			baseSearch.erase(baseSearch.begin() + index);
//		}
//	}
//

	expression = Expression();
	int plus_pos, minus_pos, min_pos, x_pos, max_pos = 1, exp_pos;

	double coef, exponent;

	int i = 0;
	while (max_pos != string::npos)
	{
		//cout << baseList[0] << baseList[1] << baseList[2];
		
		first = 0;
		for (string baseStr : BASE::globalBaseList)
		{
			if (str.find(baseStr) <= first)
			{
				first = str.find(baseStr);
				base = baseStr;
			}
		}
		
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

		string token = str;
		if(min_pos != string::npos)
			token = str.substr(0, min_pos);

		if (min_pos != string::npos)
			str = str.substr(min_pos);

		exp_pos = token.find("^");
		x_pos = token.find(base);
		
		coef = 1  ;
		if(exp_pos != 1)
			if(x_pos != 0)
				coef = stod(token.substr(0, x_pos));
			else
				coef = 1;
		
		// cout << coef;
		if (exp_pos != string::npos)
			exponent = stod(token.substr(exp_pos + 1));
		else if (x_pos != string::npos)
			exponent = 1;
		else
			exponent = 0;

		expression.addTerm(coef, exponent , base);
		i++;
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



