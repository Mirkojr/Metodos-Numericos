#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "metodos.h" // Necessário para acessar as structs de resultado

using namespace std;

// Struct para armazenar uma linha do quadro resumo
struct LinhaSistema {
    string id; 
    double valJacobi;
    double valSeidel;
};

//função auxiliar para imprimir caracteres repetidos
void imprimirRepetido(string s, int n);

//função para ler dados de entrada
void lerDadosEntrada(int& n, vector<vector<double>>& A, vector<double>& b, double& epsilon, int& iterMax);

//funções de interface
void exibirCabecalhoPrincipal();
void imprimirMatrizEstilizada(int n, const vector<vector<double>>& M, string titulo);
void imprimirResultadoVetor(const string& titulo, const vector<double>& v);
void printa_historico(const vector<struct DadosIteracao>& h, string titulo);
void quadroResumoSistemas(const vector<LinhaSistema>& tabela, DadosIteracao ultimoJ, DadosIteracao ultimoS);
void quadroResultadosVetor(const vector<double>& resJacobi, const vector<double>& resSeidel);
void mostrarAnaliseSismica(int n, const vector<double>& deslocamentos, string titulo);


#endif