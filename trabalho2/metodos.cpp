#include "metodos.h"

vector<vector<double>> calcula_inversa(int n, vector<vector<double>> A) {
    // Criar a matriz identidade I
    vector<vector<double>> I(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        I[i][i] = 1;
    }

    // Aplicar o método de Gauss-Jordan
    for (int i = 0; i < n; i++) {
        // Tornar o elemento A[i][i] igual a 1 e ajustar a matriz I
        double diag = A[i][i];
        for (int j = 0; j < n; j++) {
            A[i][j] /= diag;
            I[i][j] /= diag;
        }

        // Tornar os outros elementos da coluna i iguais a 0
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < n; j++) {
                    A[k][j] -= A[i][j] * factor;
                    I[k][j] -= I[i][j] * factor;
                }
            }
        }
    }

    return I;
}

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

void printa_matriz(int n, vector<vector<double>> M) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
        cout << M[i][j] << " ";
        }
        cout << endl;
    }
}
