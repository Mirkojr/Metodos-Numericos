#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "metodos.h" // Necessário para acessar as structs de resultado

using namespace std;

struct LinhaSistema {
    string id; 
    double valJacobi;
    double valSeidel;
};

void imprimirRepetido(string s, int n);
void imprimirMatrizEstilizada(int n, const vector<vector<double>>& M, string titulo);
void imprimirResultadoVetor(const string& titulo, const vector<double>& v);
void printa_historico(const vector<struct DadosIteracao>& h);

void quadroResumoSistemas(const vector<LinhaSistema>& tabela, DadosIteracao ultimoJ, DadosIteracao ultimoS);
void quadroResultadosVetor(const vector<double>& resJacobi, const vector<double>& resSeidel);
void mostrarAnaliseSismica(int n, const vector<double>& deslocamentos, string titulo);
void exibirCabecalhoPrincipal();

void lerDadosEntrada(int& n, vector<vector<double>>& A, vector<double>& b, double& epsilon, int& iterMax);

#endif