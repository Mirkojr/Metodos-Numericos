#include <iostream>
#include <cmath>
#include "metodos.h"

using namespace std;


Metodos::Metodos(const string& func){
    this->func = func;
}

void Metodos::setFunc(string func){
    this->func = func;
}

void Metodos::setPhi(string phi){
    this->phiFunc = phi;
}

void Metodos::printFunc(){
    cout << this->func << endl;
}

double Metodos::F(double x){
    return this->fParser.parse(this->func, x);
}

double Metodos::Phi(double x){
    return this->fParser.parse(this->phiFunc, x);
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

double Metodos::choose(double a, double b) {
    return (abs(F(a)) < abs(F(b))) ? a : b;
}

double Metodos::falsePosition(double a, double b, double epsilon1, double epsilon2, int maxIter){
    double root;

    double Fa = F(a);
    double Fb = F(b);

    cout << "Fa: " << Fa << endl;
    cout << "Fb: " << Fb << endl;

    if (Fa * Fb > 0){
        cout << "This function don't change signals between a and b." << endl;
        return NAN;
    }

    double intervX = abs(b-a);
    if(intervX < epsilon1) return choose(a,b);
    if(abs(F(a)) < epsilon2) return a;
    if(abs(F(b)) < epsilon2) return b;
    
    int k = 0;
    double x; double Fx;
    while(true){
        x = (a*F(b) - b*(F(a)))/(F(b)-F(a));
        Fx = F(x);
        cout << "K :" << k << endl;
        if((abs(Fx) < epsilon2) || (k>=maxIter)){
            root = x;
            break;
        }
        if(Fa*Fx > 0){
            a = x;
            Fa = Fx;
        }
        else{
            b = x;
            Fb = Fx;
        }

        intervX = abs(b-a);

        if(intervX <= epsilon1){
            root = choose(a,b);
            break;
        }

        k++;
    }
    
    return root;
}

double Metodos::fixedPoint(double x0, double epsilon1, double epsilon2, int maxIter){

    //check if Phi was defined ** required **
    if (this->phiFunc.empty()) return NAN;


    if(abs(F(x0)) < epsilon1) return x0;

    int k = 1;
    while(true){
        double x1 = Phi(x0);
        if(abs(F(x1)) < epsilon1 || abs(x1-x0) < epsilon2 || k >= maxIter) return x1;
        x0 = x1;
        k++;
    }
}