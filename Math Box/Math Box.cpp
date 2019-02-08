// Math Box.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ExpParser.h"

int main()
{
	string str;
	cout << "Enter Function : \n";
	cin >> str;

	Parser parser;
	parser.setString(str);
	parser.simpleParse();

	Integrator integratorLeft, integratorRight, integratorMid;

	integratorLeft.fit(&parser, Left);
	integratorRight.fit(&parser, Right);
	integratorMid.fit(&parser, Mid);

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
		printOutput(left, right, n, resultMid, resultLeft, resultRight, blockSimplify(parser.getTerms()));
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
void printOutput(double left, double right, int n, double intM, double intL, double intR, vector<Term> function)
{
	cout << "With Step Size: " << (right - left) / n << " \n";
	cout << "The approximate integral of the f(x) = ";
	printFunc(function);
	cout << " \n";
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
