#pragma once
#include<string>
#include<vector>
class BASE
{
public:
	std::string baseFunc;


	BASE(std::string);

	BASE();

	double eval(double x);

	static std::vector<std::string> globalBaseList;
	static std::string globalBase;
};


