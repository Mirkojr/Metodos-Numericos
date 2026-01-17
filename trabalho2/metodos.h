#ifndef METODOS_H
#define METODOS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

// struct para armazenar dados de cada iteração
struct DadosIteracao {
    int k;
    double norma;
    vector<double> x;
};

vector<vector<double>> calculaInversaJacobi(int n, vector<vector<double>> A, double epsilon, int iterMax);
vector<vector<double>> calculaInversaSeidel(int n, vector<vector<double>> A, double epsilon, int iterMax);
vector<double> multiplicarMatrixVetor(int n, vector<vector<double>> M, vector<double> v);
double calcula_norma(int n, vector<double> &x, vector<double> &v);

vector<double> Gauss_Jacobi(int n, vector<vector<double>> A, vector<double> b, double epsilon, int iterMax, vector<struct DadosIteracao>* historico = nullptr);
vector<double> Gauss_Seidel(int n, vector<vector<double>> A, vector<double> b, double e, int iterMax, vector<struct DadosIteracao>* historico = nullptr);

void printa_matriz(int n, vector<vector<double>> M);
void printa_historico(const vector<struct DadosIteracao>& h);

#endif // METODOS_H
