#include <iostream>
#include <cmath>
#include "metodos.h"

using namespace std;


Metodos::Metodos(const string& func){
    this->func = func;
}

void Metodos::printFunc(){
    cout << this->func << endl;
}

double Metodos::F(double x){
    return this->fParser.parse(this->func, x);
}

double Metodos::bissecao( double a, double b, double epslon, int maxIter){
    double Fa = F(a);
    double Fb = F(b);

    cout << Fa << endl;
    cout << Fb << endl;

    if (Fa * Fb > 0){
        cout << "This function don't change signals between a and b." << endl;
        return NAN;
    }

    double intervX = abs(b-a);
    int k = 0;
    double x;
    while(true){
        x = (a+b)/2; 
        double Fx = F(x);

        if(intervX <= epslon || k >= maxIter) break;
        if(Fa*Fx > 0){
            a = x;
            Fa = Fx;
        }
        else{
            b = x;
            Fb = Fx;
        }
        intervX = intervX/2;
        k++;
    }   
    return x;
}

