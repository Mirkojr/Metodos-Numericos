#include "functionParser.h"
#include "metodos.h"
#include <iostream>

using namespace std;



int main(){

    Metodos metodos("x^3 - 9 * x + 3");
    metodos.printFunc();

    FunctionParser fParser;

    // cout << metodos.bissecao(0, 1, 10*pow(10, -4), 10) << endl;
    double eps = 0.5 * pow(10, -3);
    double resultFalsePosition = metodos.falsePosition(0, 1, eps, eps, 3);
    cout << "Posicao falsa: " << resultFalsePosition << endl;
    return 0;
}

