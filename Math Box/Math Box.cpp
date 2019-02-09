// Math Box.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "Parser.h"
#include "Function.h"
#include "Integrator.h"
#include "Differentiator.h"
#include "constants.h"

int main();

bool validateInput(double left, double right, int n);
void printOutput(double left, double right, int n, double intM, double intL, double intR, string function);
void getInputs(double &left, double &right, int &n);

// Menu and operations
void IntegrateFunc(Function);
void SimplifyFunc(Function func);
void DifferentiateFunc(Function);
void help();

int main()
{
	string str , function , command;
	Parser parser;
	Function func;


	while (true)
	{
		cout << "\nEnter Command: type HELP for help \n" << ">>";
		getline(cin, str);


		function = str.substr(4);
		command = str.substr(0, 4);

		if (command == "EXT ")
			exit(0);

		if (command == "HELP" || command == "help")
		{
			help();
			continue;
		}
		
		parser.setString(function);
		parser.parse();
		func = parser.getFunction();

		cout << "Function Parsed Successfully!";
		command = str.substr(0, 4);
		
		
		if (command == "INT ")
			IntegrateFunc(func);
		if (command == "SIM ")
			SimplifyFunc(func);
		if (command == "DIF ")
			DifferentiateFunc(func);
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
void DifferentiateFunc(Function func)
{
	Differentiator diff;
	double x;
	diff.fit(&func, 0.001);
	cout << "\n Enter point to differentiate: ";
	cin >> x;

	cout << "Slope of f(x) at x = " << x << " is: " << diff.eval(x); 
}

void help()
{
	cout << "Available Commands: \n"
		<< "SIM  <function> - Simpify Function \n"
		<< "INT  <function> - Integrate Function\n"
		<< "DIF  <function> - Differentiate Function\n"
		<< "HELP <function> - Display this help Box\n"
		<< "EXT  - Exit\n"
		<< "NOTE: (Always Type a coefficient with x and parenthesis )";
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
