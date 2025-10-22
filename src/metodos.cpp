#include <iostream>
#include "metodos.h"

using namespace std;


Metodos::Metodos(const string& func){
    this->func = func;
}

void Metodos::printFunc(){
    cout << this->func << endl;
}

double Metodos::bissecao( double a, double b, double epslon, int maxIter){
    double root; 

    double Fa = this->fParser.parse(this->func, a);
    double Fb = this->fParser.parse(this->func, b);

    cout << Fa << endl;
    cout << Fb << endl;
    return root;
}

