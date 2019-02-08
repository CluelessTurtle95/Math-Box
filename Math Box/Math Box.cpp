// Math Box.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ExpParser.h"
#include"Expression.h"
#include"Integrator.h"
#include"constants.h"

bool validateInput(double left, double right, int n);
void printOutput(double left, double right, int n, double intM, double intL, double intR, string function);
void getInputs(double &left, double &right, int &n);

int main()
{
	string str;
	cout << "Enter Function : \n";
	cin >> str;

	ExpParser expParser;
	expParser.setString(str);
	expParser.parse();
	Expression e = expParser.getExpression();

	Integrator integratorLeft, integratorRight, integratorMid;

	integratorLeft.fit(&Function::to_func(e), Left);
	integratorRight.fit(&Function::to_func(e), Right);
	integratorMid.fit(&Function::to_func(e), Mid);

	double left, right;
	int n;
	getInputs(left, right, n);
	if (left*left + right * right + n * n == 0)
		return 0;

	while (!validateInput(left, right, n))
	{
		cout << "Invalid Inputs...";
		getInputs(left, right, n);
	}

	{
		double resultLeft = integratorLeft.eval(left, right, n);
		double resultRight = integratorRight.eval(left, right, n);
		double resultMid = integratorMid.eval(left, right, n);
		printOutput(left, right, n, resultMid, resultLeft, resultRight, e.getString());
	}
	cin >> left;
	return 0;
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
