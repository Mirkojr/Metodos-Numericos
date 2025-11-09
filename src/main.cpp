#include "functionParser.h"
#include "metodos.h"
#include <iostream>

using namespace std;

void testFalsePosition(){
    cout << "Testing Newton-Raphson :" << endl;
    Metodos metodos("(x^3) - 9 * x + 3");
    metodos.printFunc();

    double a = 0;
    double b = 1;
    double x0 = 0.5;
    double eps = 0.5 * pow(10, -3);
    int maxIter = 3;
    
    double resultFalsePosition = metodos.falsePosition(a, b, eps, eps, maxIter);
    cout << "False position: " << resultFalsePosition << endl;
}

void testNewtonRaphson(){
    cout << "Testing Newton-Raphson :" << endl;
    Metodos metodos("(x^3) - 9 * x + 3");
    string derivate = "3 * (x ^ 2) - 9";
    metodos.setDerivate(derivate);
    metodos.printFunc();

    double x0 = 0.5;
    double eps = 0.5 * pow(10, -3);
    int maxIter = 3;

    double resultNewtonRaphson = metodos.newtonRaphson(x0, eps, eps, maxIter);
    cout << "NewtonRaphson: " << resultNewtonRaphson << endl;
}

double testSecante(){
    cout << "Testing Secant Method :" << endl;
    Metodos metodos("(x^3) - 9 * x + 3");
    metodos.printFunc();

    double x0 = 0;
    double x1 = 1;
    double eps = 0.5 * pow(10, -3);
    int maxIter = 3;

    double resultSecante = metodos.secante(x0, x1, eps, eps, maxIter);
    cout << "Secant Method: " << resultSecante << endl;
    return resultSecante;
}

int main(){

    testFalsePosition();
    testNewtonRaphson();
    testSecante();
    return 0;
}

