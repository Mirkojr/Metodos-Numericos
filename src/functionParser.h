#ifndef FUNCTION_PARSER_H
#define FUNCTION_PARSER_H

#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <algorithm> // for std::any_of
using namespace std;

class FunctionParser{
    string variableToValue(string function, char variable, double value);

    public:

    double evaluateOp(double a, char op, double b);
    int precedence(char op);
    double parse(const string& funcWithoutVar, double value);
    double parse(const string& funcWithoutVar);
    double parse(const string& funcWithVar, char variable, double value);
    void test();
};
 


#endif