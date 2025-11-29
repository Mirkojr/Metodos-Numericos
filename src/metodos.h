#ifndef METODOS_H
#define METODOS_H

#include "functionParser.h"

struct Resultado{
    double raiz;
    int iteracoes;
    double erro;
};

class Metodos{

    // atributos auxiliares
    string func;
    string phiFunc;
    string derivate;
    FunctionParser fParser;

    // metodos auxiliares
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

        // metodos basicos
        double bissecao( double a, double b, double epsilon, int maxIter);
        double posicaoFalsa(double a, double b, double epsilon1, double epsilon2, int maxIter);
        double pontoFixo(double x0, double epsilon1, double epsilon2, int maxIter);

        // metodos avancados
        Resultado newtonRaphson(double x0, double epsilon1, double epsilon2, int maxIter);
        Resultado secante(double x0, double x1, double epsilon1, double epsilon2, int maxIter);
        Resultado newtonRaphsonModificado(double x0, double epsilon1, double epsilon2, int maxIter);
};

#endif
