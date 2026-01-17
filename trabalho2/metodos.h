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

// matriz e vetor
void le_vetor(int n, vector<double>& b);
void printa_vetor(const vector<double>& v);
void le_matriz(int n, vector<vector<double>>& A);
void printa_matriz(int n, vector<vector<double>> M);
void produto_e_imprime(int n, const vector<vector<double>>& M, const vector<vector<double>>& Inv, const vector<double>& b);
vector<double> multiplicarMatrixVetor(int n, vector<vector<double>> M, vector<double> v);

// algoritmos auxiliares
double calcula_norma(int n, vector<double> &x, vector<double> &v);
vector<vector<double>> calculaInversaJacobi(int n, vector<vector<double>> A, double epsilon, int iterMax);
vector<vector<double>> calculaInversaSeidel(int n, vector<vector<double>> A, double epsilon, int iterMax);

// metodos
vector<double> Gauss_Jacobi(int n, vector<vector<double>> A, vector<double> b, double epsilon, int iterMax, vector<struct DadosIteracao>* historico = nullptr);
vector<double> Gauss_Seidel(int n, vector<vector<double>> A, vector<double> b, double e, int iterMax, vector<struct DadosIteracao>* historico = nullptr);

// menu
void menu();
void printa_historico(const vector<struct DadosIteracao>& h);
void printa_matriz_e_vetor(int n, vector<vector<double>> A, vector<double> b);
void limpa_tela();
