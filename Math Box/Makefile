all: Math

CC=g++
CFAGS= -c -Wall

Math: main.o BASE.o Term.o Expression.o ExpTerm.o Function.o ExpParser.o Parser.o Integrator.o Differentiator.o Solver.o
	$(CC) $(CFAGS) main.o BASE.o Term.o Expression.o ExpTerm.o Function.o ExpParser.o Parser.o -o Math
main.o: 'Math Box.cpp' constants.h
	$(CC) $(CFAGS) 'Math Box.cpp'
BASE.o: BASE.cpp constants.h
	$(CC) $(CFAGS) BASE.cpp
Term.o: Term.cpp constants.h
	$(CC) $(CFAGS) Term.cpp
Expression.o: Expression.cpp constants.h
	$(CC) $(CFAGS) Expression.cpp
ExpTerm.o: ExpTerm.cpp constants.h
	$(CC) $(CFAGS) ExpTerm.cpp
Function.o: Function.cpp constants.h
	$(CC) $(CFAGS) Function.cpp
ExpParser.o: ExpParser.cpp constants.h
	$(CC) $(CFAGS) ExpParser.cpp
Parser.o: Parser.cpp constants.h
	$(CC) $(CFAGS) Parser.cpp
Integrator.o: Integrator.cpp constants.h
	$(CC) $(CFAGS) Integrator.cpp
Differentiator.o: Differentiator.cpp constants.h
	$(CC) $(CFAGS) Differentiator.cpp
Solver.o: Solver.cpp constants.h
	$(CC) $(CFAGS) Solver.cpp