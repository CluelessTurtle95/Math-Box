#pragma once
#include<string>
#include<vector>
#include<string>

using namespace std;

class Base
{
	bool combo;
	string comboFunc1;
	string comboFunc2;

public:
	std::string baseFunc;
	
	void setCombo(string func1 , string func2);

	Base(std::string);
	Base();
	double eval(double x);
	Base static combine(Base a, Base b);
	static std::vector<std::string> globalBaseList;
	static std::string globalBase;
};


