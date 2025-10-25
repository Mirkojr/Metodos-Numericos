
#ifndef METODOS_H
#define METODOS_H

#include <iostream>
#include "functionParser.h"

class Metodos{
    string func;
    FunctionParser fParser;

    double F(double x);

    public:
    Metodos(const string& func);
    void printFunc();
    double bissecao( double a, double b, double epslon, int maxIter);
};

#endif 