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

vector<double> Gauss_Jacobi(int n, vector<vector<double>> A, vector<double> b, double epsilon, int iterMax) {
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

    cout << fixed << setprecision(6);

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
        
        // Saída de controle
        // cout << "Iteracao k=" << k << " | Norma=" << norma << endl;
        cout << "Iteracao k=" << k << " | Norma: " << norma << " | x: ";
        for (double val : x) cout << val << " ";
        cout << endl;

        // se norma <= epsilon ou k >= iterMax então interrompa
        if (norma <= epsilon || k >= iterMax) {
            break;
        }
    }

    return x; // Retorna o vetor solução x
}

// Algoritmo principal: Gauss_Seidel (conforme Fonte [2])
vector<double> Gauss_Seidel(int n, vector<vector<double>> A, vector<double> b, double e, int iterMax) {
    vector<double> x(n);
    vector<double> v(n);

    // 1. Construção da matriz e do vetor de iterações inicial [2]
    for (int i = 0; i < n; i++) {
        double r = 1.0 / A[i][i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                A[i][j] = A[i][j] * r;
            }
        }
        b[i] = b[i] * r;
        x[i] = b[i]; // Aproximação inicial xi = bi/aii [2, 4]
    }

    int k = 0;
    double norma;

    cout << fixed << setprecision(6);

    // 2. Iterações de Gauss-Seidel [2]
    do {
        k = k + 1;
        for (int i = 0; i < n; i++) {
            double soma = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    // Diferente de Jacobi, Seidel usa os valores de x já atualizados [1]
                    soma = soma + A[i][j] * x[j];
                }
            }
            v[i] = x[i];          // Guarda o valor anterior para o cálculo da norma [2]
            x[i] = b[i] - soma;   // Atualiza x[i] imediatamente [2]
        }

        // 3. Cálculo da norma de erro relativo [2, 3]
        norma = calcula_norma(n, v, x);

        cout << "Iteracao k=" << k << " | Norma: " << norma << " | x: ";
        for (double val : x) cout << val << " ";
        cout << endl;

        // 4. Critério de parada: precisão alcançada ou limite de iterações [2, 5]
        if (norma <= e || k >= iterMax) {
            break;
        }

    } while (true);

    return x;
}

void printa_matriz(int n, vector<vector<double>> M) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
        cout << M[i][j] << " ";
        }
        cout << endl;
    }
}
