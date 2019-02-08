// Math Box.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "Parser.h"
#include "Function.h"
#include "Integrator.h"
#include "constants.h"

int main();

bool validateInput(double left, double right, int n);
void printOutput(double left, double right, int n, double intM, double intL, double intR, string function);
void getInputs(double &left, double &right, int &n);

// Menu and operations
void IntegrateFunc(Function);
void SimplifyFunc(Function func);
void help();

int main()
{
	string str;
	cout << "Enter Function : (Always Type a coefficient with x and parenthesis )\n";
	getline(cin, str);

	Parser parser;
	parser.setString(str);
	parser.parse();
	Function func = parser.getFunction();

	while (true)
	{
		cout << "\n Function Parsed Successfully! Enter Command: type HELP for help \n";
		getline(cin, str);
		if (str == "HELP")
			help();
		if (str == "EXT")
			exit(0);
		if (str == "INT")
			IntegrateFunc(func);
		if (str == "SIM")
			SimplifyFunc(func);
	}
	char ch;
	cin >> ch;
	return 0;
}

void IntegrateFunc(Function func)
{
	Integrator integratorLeft, integratorRight, integratorMid;

	integratorLeft.fit(&func, Left);
	integratorRight.fit(&func, Right);
	integratorMid.fit(&func, Mid);

	double left, right;
	int n;
	getInputs(left, right, n);
	if (left*left + right * right + (double)n * (double)n == 0)
		return ;

	while (!validateInput(left, right, n))
	{
		cout << "Invalid Inputs...";
		getInputs(left, right, n);
	}

	{
		double resultLeft = integratorLeft.eval(left, right, n);
		double resultRight = integratorRight.eval(left, right, n);
		double resultMid = integratorMid.eval(left, right, n);
		func.simplify();
		printOutput(left, right, n, resultMid, resultLeft, resultRight, func.getString());
	}
}
void SimplifyFunc(Function func)
{
	func.simplify();
	cout << "\n Simplified Function: " << func.getString();
}

void help()
{
	cout << "Available Commands: \n"
		<< "SIM  - Simpify Function \n"
		<< "INT  - Integrate Function\n"
		<< "HELP - Display this help Box\n"
		<< "EXT  - Exit\n";
}

bool validateInput(double left, double right, int n)
{
	if (left < -10)
		return false;
	if (right > 10)
		return false;
	if (left > right)
		return false;
	if (n <= 0)
		return false;

	return true;
}
void printOutput(double left, double right, int n, double intM, double intL, double intR, string function)
{
	cout << "With Step Size: " << (right - left) / n << " \n";
	cout << "The approximate integral of the f(x) = " << function << " \n";
	cout << "Bound between " << left << " and " << right << ", using " << n << " rectangles is as follows \n";
	cout << "\nMid point evaluation approximate:  " << intM;
	cout << "\nLeft point evaluation approximate: " << intL;
	cout << "\nRight point evaluation approximate:" << intR;
}
void getInputs(double &left, double &right, int &n)
{
	cout << "\nEnter the Left boundary: a, Right boundary: b, and No. of rectangles to use.\nTo exit enter 0 0 0";
	cin >> left >> right >> n;
}
