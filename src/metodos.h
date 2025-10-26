
#ifndef METODOS_H
#define METODOS_H

#include <iostream>
#include "functionParser.h"

class Metodos{
    string func;
    FunctionParser fParser;

    double F(double x);
    double choose(double a, double b);

    public:
    Metodos(const string& func);
    void printFunc();
    double bissecao( double a, double b, double epsilon, int maxIter);
    double falsePosition(double a, double b, double epsilon1, double epsilon2, int maxIter);
};

#endif 