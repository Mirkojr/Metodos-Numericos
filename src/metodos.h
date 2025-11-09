
#ifndef METODOS_H
#define METODOS_H

#include <iostream>
#include "functionParser.h"

class Metodos{
    string func;
    string phiFunc;
    string derivate;
    FunctionParser fParser;

    double F(double x);
    double Phi(double x);
    double D(double x);
    double choose(double a, double b);
    
    public:
    Metodos(const string& func);
    void printFunc();
    void setPhi(string phi);
    void setFunc(string func);
    void setDerivate(string derivate);

    double bissecao( double a, double b, double epsilon, int maxIter);
    double falsePosition(double a, double b, double epsilon1, double epsilon2, int maxIter);
    double fixedPoint(double x0, double epsilon1, double epsilon2, int maxIter);
    double newtonRaphson(double x0, double epsilon1, double epsilon2, int maxIter);
    double secante(double x0, double x1, double epsilon1, double epsilon2, int maxIter);
    double newtonRaphsonModificado(double x0, double epsilon1, double epsilon2, int maxIter);
};

#endif 