#include "functionParser.h"
#include "metodos.h"
#include <iostream>

using namespace std;



int main(){

    Metodos metodos("x^2 + 3*x + 1");
    metodos.printFunc();

    FunctionParser fParser;

    cout << fParser.parse("x^2 + 3*x + 1", 3) << endl;

    metodos.bissecao(3, 5, 2, 3);

    return 0;
}

