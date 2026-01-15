#ifndef FUNCTION_PARSER_H
#define FUNCTION_PARSER_H

#include <algorithm> // std::any_of
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <stack>

using namespace std;

class FunctionParser{
    string variableToValue(string function, char variable, double value);

    public:

        double evaluateOp(double a, char op, double b);
        int precedence(char op);
        double parse(const string& funcWithoutVar, double value);
        double parse(const string& funcWithoutVar);
        double parse(const string& funcWithVar, char variable, double value);
};

#endif
