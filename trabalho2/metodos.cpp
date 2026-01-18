#include "metodos.h"

double calcula_norma(int n, vector<double> &x, vector<double> &v) {
    double normaNum = 0.0;
    double normaDen = 0.0;

    for (int i = 0; i < n; ++i) {
        double t = abs(v[i] - x[i]);
        if (t > normaNum) {
            normaNum = t;
        }
        if (abs(v[i]) > normaDen) {
            normaDen = abs(v[i]);
        }

        // Atualiza o vetor x com o vetor v
        x[i] = v[i];
    }

    double norma = normaNum / normaDen;
    return norma;
}

vector<double> Gauss_Jacobi(int n, vector<vector<double>> A, vector<double> b, double epsilon, int iterMax, vector<DadosIteracao>* historico) {
    vector<double> x(n);
    vector<double> v(n);
    int k = 0;

    // {construção da matriz e do vetor de iterações}
    for (int i = 0; i < n; i++) {
        double r = 1.0 / A[i][i]; // r <- 1/A[i][i]
        for (int j = 0; j < n; j++) {
            if (i != j) {
                A[i][j] = A[i][j] * r; // A[i][j] <- A[i][j] * r
            }
        }
        b[i] = b[i] * r; // b[i] <- b[i] * r
        x[i] = b[i];     // x[i] <- b[i]
    }

    // {iterações de Jacobi}
    while (true) {
        k = k + 1; // k <- k + 1
        
        for (int i = 0; i < n; i++) {
            double soma = 0; // soma <- 0
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    soma = soma + A[i][j] * x[j]; // soma <- soma + A[i][j] * x[j]
                }
            }
            v[i] = b[i] - soma; // v[i] <- b[i] - soma
        }

        double norma = calcula_norma(n, x, v); // norma <- calcula_norma(n,x,v)
        
        // Saída de debug
        if (historico != nullptr) {
            historico->push_back({k, norma, x});
        }

        // se norma <= epsilon ou k >= iterMax então interrompa
        if (norma <= epsilon || k >= iterMax) {
            break;
        }
    }

    return x; // Retorna o vetor solução x
}

// Algoritmo principal: Gauss_Seidel
vector<double> Gauss_Seidel(int n, vector<vector<double>> A, vector<double> b, double e, int iterMax, vector<DadosIteracao>* historico) {
    vector<double> x(n);
    vector<double> v(n);

    // Construção da matriz e do vetor de iterações inicial 
    for (int i = 0; i < n; i++) {
        double r = 1.0 / A[i][i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                A[i][j] = A[i][j] * r;
            }
        }
        b[i] = b[i] * r;
        x[i] = b[i]; // Aproximação inicial xi = bi/aii 
    }

    int k = 0;
    double norma;

    // Iterações de Gauss-Seidel 
    do {
        k = k + 1;
        for (int i = 0; i < n; i++) {
            double soma = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    // Diferente de Jacobi, Seidel usa os valores de x já atualizados 
                    soma = soma + A[i][j] * x[j];
                }
            }
            v[i] = x[i];          // Guarda o valor anterior para o cálculo da norma
            x[i] = b[i] - soma;   // Atualiza x[i] imediatamente 
        }

        // Cálculo da norma de erro relativo 
        norma = calcula_norma(n, v, x);

        // Armazena o histórico
        if (historico != nullptr) {
            historico->push_back({k, norma, x});
        }

        // Critério de parada: precisão alcançada ou limite de iterações 
        if (norma <= e || k >= iterMax) {
            break;
        }

    } while (true);

    return x;
}

vector<vector<double>> calculaInversaJacobi(int n, vector<vector<double>> A, double epsilon, int iterMax, vector<DadosIteracao>* historico) {
    vector<double> b_aux(n, 0.0);
    vector<vector<double>> matrizInversa(n, vector<double>(n, 0.0));

    for( int j = 0; j < n; j++ ) {
        b_aux[j] = 1.0;
        vector<double> coluna_inversa = Gauss_Jacobi(n, A, b_aux, epsilon, iterMax, historico);
        b_aux[j] = 0.0;

        for( int i = 0; i < n; i++ ) {
            matrizInversa[i][j] = coluna_inversa[i];
        }
    }
    return matrizInversa;
}

vector<vector<double>> calculaInversaSeidel(int n, vector<vector<double>> A, double epsilon, int iterMax, vector<DadosIteracao>* historico) {
    vector<double> b_aux(n, 0.0);
    vector<vector<double>> matrizInversa(n, vector<double>(n, 0.0));

    for( int j = 0; j < n; j++ ) {
        b_aux[j] = 1.0;
        vector<double> coluna_inversa = Gauss_Seidel(n, A, b_aux, epsilon, iterMax, historico);
        b_aux[j] = 0.0;

        for( int i = 0; i < n; i++ ) {
            matrizInversa[i][j] = coluna_inversa[i];
        }
    }
    return matrizInversa;
}

vector<double> multiplicarMatrixVetor(int n, vector<vector<double>> M, vector<double> v) {
    vector<double> resultado(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultado[i] += M[i][j] * v[j];
        }
    }

    return resultado;
}


