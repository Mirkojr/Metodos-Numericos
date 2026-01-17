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

// Protótipos das funções de exibição
void imprimirRepetido(string s, int n);
void imprimirMatrizEstilizada(int n, const vector<vector<double>>& M, string titulo);
void quadroResumoSistemas(const vector<LinhaSistema>& tabela, DadosIteracao ultimoJ, DadosIteracao ultimoS);
void mostrarAnaliseSismica(int n, const vector<double>& deslocamentos);
void exibirCabecalhoPrincipal();
void lerDadosEntrada(int& n, vector<vector<double>>& A, vector<double>& b, double& epsilon, int& iterMax);

#endif