// Math Box.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include "Parser.h"
#include "Function.h"
#include "Integrator.h"
#include "Differentiator.h"
#include "Solver.h"
#include "constants.h"

int main();

// Integrator Help functions
bool validateInput(double left, double right, int n);
void printOutput(double left, double right, int n, double intM, double intL, double intR, string function);
void getInputs(double &left, double &right, int &n);

// Function To check values before input
double check(string str);

// Menu and operations
void IntegrateFunc(Function); // Menu For integration
void SimplifyFunc(Function func); // Menu For Simpification
void DifferentiateFunc(Function); // Menu For Differentiation
void SolveFunc(Function); // Menu For Solving
void help(); // Help box

int main()
{
	// Variable Declarations
	string str , function , command;
	Parser parser;
	Function func;

	// Taking user input
	// Entering Infinite loop for command - line inteface
	cout << "\nEnter Command: type HELP for help \n" ;
	while (true)
	{
		cout << ">>";
		getline(cin, str);
		if (Parser::removeChar(str, ' ') == "")
			continue;

		// Seperating Command and function -  string
		function = str.substr(str.find(" ")+1);
		command = str.substr(0, str.find(" "));

		// Creating parser object to parse function string
		parser = Parser();

		// Checking Various commands
		if (command == "EXT " || command == "EXT")
			exit(0);

		if (str == "help func")
		{
			for (string str : BASE::globalBaseList)
			{
				cout << str;
				if (str != BASE::globalBaseList.at(BASE::globalBaseList.size() - 1))
					cout << " , ";
			}
			cout << endl;
			continue;
		}

		if (command == "HELP" || command == "help")
		{
			help();
			continue;
		}
		
		// Setting function to parser after making sure user wants computation
		parser.setString(function);
		try
		{
			parser.parse();
		}
		catch (const exception &)
		{
			cerr << "Invalid Command Argument!" << endl;
			continue;
		}
		// For Each command, function is created and then passed to appropriate menu
		if (command == "INT")
		{
			
			func = parser.getFunction();
			IntegrateFunc(func);
		}
		else if (command == "SIM")
		{
			func = parser.getFunction();
			SimplifyFunc(func);
		}
		else if (command == "DIF")
		{
			func = parser.getFunction();
			DifferentiateFunc(func);
		}
		else if (command == "SOLVE")
		{
			func = parser.getFunction();
			SolveFunc(func);
		}
		else
			cout << command << " : Command Not Found!\n";
	}

	// So program doesnt end abrubtly
	char ch = ' ';
	cin >> ch;
	return 0;
}

// All operation Classes have a fit(Function *, ...) and an eval(double) methods.

void IntegrateFunc(Function func)
{
	// Creating Integrator Objects
	Integrator integratorLeft, integratorRight, integratorMid;

	// Passing the function and additional information about required computation
	integratorLeft.fit(&func, Left);
	integratorRight.fit(&func, Right);
	integratorMid.fit(&func, Mid);

	double left, right;
	int n;
	getInputs(left, right, n);

	// Checking if user inputs 0 0 0
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
	try
	{
		func.simplify();
	}
	catch (const std::exception&)
	{
		cerr << "Invalid Function Entered!";
		return;
	}
	
	string temp = func.getString();
	
	while (temp.find("+1.(") != string::npos)
		temp.replace(temp.find("+1.("), 4, "+");
	while (temp.find(")^1.") != string::npos)
		temp.replace(temp.find(")^1."), 4, "");
	/*
	temp = Parser::removeChar(temp, ' ');
	Parser parser;
	parser.setString(temp);
	parser.parse();
	temp = parser.getFunction().getString();
	while (temp.find("+1.(") != string::npos)
		temp.replace(temp.find("+1.("), 4, "+");
	while (temp.find(")^1.") != string::npos)
		temp.replace(temp.find(")^1."), 4, "");
	*/
	cout << "\n Simplified Function: " << temp << "\n";

}
void DifferentiateFunc(Function func)
{
	string input;
	Differentiator diff;
	double x;
	diff.fit(&func, DiffDelX);
	cout << "\n Enter point to differentiate: ";
	getline(cin, input);
	x = check(input);
	if(x != InvalidValue)
		cout << "Slope of f(x) at x = " << x << " is: " << diff.eval(x)<< "\n"; 
}
void SolveFunc(Function func) 
{
	string input;
	Solver solver;
	double guess;
	solver.fit(&func);
	while(true)
	{ 
		cout << "\nEnter Initial Guess : (Enter " << InvalidValue << " to Exit) : ";
		getline(cin, input);
		guess = check(input);

		if (guess == InvalidValue)
			return;
		double result = solver.eval(guess);
		if(result != InvalidValue)
			cout << "Solution for f(x) = 0 is x = " <<  result << "\n";
	}
}

void help()
{
	cout << "Available Commands: \n"
		<< "SIM   <function> - Simpify Function \n"
		<< "INT   <function> - Integrate Function\n"
		<< "DIF   <function> - Differentiate Function\n"
		<< "SOLVE <function> - solve for f(x) = 0\n"
		<< "HELP             - Display this help Box\n"
		<< "EXT  - Exit\n"
		<< "Type help func to see available base Functions. \n"
		<< "NOTE: (Always Type a coefficient with x and parenthesis )\n";
		
}

// Function to check parameters for integration operation
bool validateInput(double left, double right, int n)
{
	if (left < - IntegratorLimit )
		return false;
	if (right > IntegratorLimit)
		return false;
	if (left > right)
		return false;
	if (n <= 0)
		return false;

	return true;
}
// Function to print Output for integration operation
void printOutput(double left, double right, int n, double intM, double intL, double intR, string function)
{
	cout << "With Step Size: " << (right - left) / n << " \n";
	cout << "The approximate integral of the f(x) = " << function << " \n";
	cout << "Bound between " << left << " and " << right << ", using " << n << " rectangles is as follows \n";
	cout << "\nMid point evaluation approximate:  " << intM;
	cout << "\nLeft point evaluation approximate: " << intL;
	cout << "\nRight point evaluation approximate:" << intR<< endl;
}
// Getting Inputs for Integration
void getInputs(double &left, double &right, int &n)
{
	cout << "\nEnter the Left boundary: a, Right boundary: b, and No. of rectangles to use.\nTo exit enter 0 0 0";
	cin >> left >> right >> n;
}


double check(string str)
{
	double d;
	try
	{
		d = stod(str);
	}
	catch (const std::exception&)
	{
		d = InvalidValue;
		cerr << "Invalid Value";
	}
	return d;
}
