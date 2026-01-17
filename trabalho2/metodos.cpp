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

// Algoritmo principal: Gauss_Seidel (conforme Fonte [2])
vector<double> Gauss_Seidel(int n, vector<vector<double>> A, vector<double> b, double e, int iterMax, vector<DadosIteracao>* historico) {
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

        if (historico != nullptr) {
            historico->push_back({k, norma, x});
        }

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

vector<vector<double>> calculaInversaJacobi(int n, vector<vector<double>> A, double epsilon, int iterMax) {
    vector<double> b_aux(n, 0.0);
    vector<vector<double>> matrizInversa(n, vector<double>(n, 0.0));

    for( int j = 0; j < n; j++ ) {
        b_aux[j] = 1.0;
        vector<double> coluna_inversa = Gauss_Jacobi(n, A, b_aux, epsilon, iterMax, nullptr);
        b_aux[j] = 0.0;

        for( int i = 0; i < n; i++ ) {
            matrizInversa[i][j] = coluna_inversa[i];
        }
    }
    return matrizInversa;
}

vector<vector<double>> calculaInversaSeidel(int n, vector<vector<double>> A, double epsilon, int iterMax) {
    vector<double> b_aux(n, 0.0);
    vector<vector<double>> matrizInversa(n, vector<double>(n, 0.0));

    for( int j = 0; j < n; j++ ) {
        b_aux[j] = 1.0;
        vector<double> coluna_inversa = Gauss_Seidel(n, A, b_aux, epsilon, iterMax, nullptr);
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

void printa_historico(const vector<DadosIteracao>& h) {
    for(const auto& reg : h) {
        cout << "k=" << reg.k << " | Norma: " << reg.norma << " | x: [ ";
        for(double val : reg.x) cout << val << " ";
        cout << "]" << endl;
    }
}

void le_matriz(int n, vector<vector<double>>& A) {
    cout << "Digite os elementos da matriz A (" << n << "x" << n << ") linha por linha:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[i][j];
        }
    }
}

void le_vetor(int n, vector<double>& b) {
    cout << "Digite os " << n << " elementos do vetor b:\n";
    for (int i = 0; i < n; ++i) cin >> b[i];
}

void printa_vetor(const vector<double>& v) {
    cout << "[ ";
    for (double x : v) cout << fixed << setprecision(3) << x << " ";
    cout << "]\n";
}

void produto_e_imprime(int n, const vector<vector<double>>& M, const vector<vector<double>>& Inv, const vector<double>& b) {
    cout << "A * A^{-1} (aprox):\n";
    vector<vector<double>> prod(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                prod[i][j] += M[i][k] * Inv[k][j];
    printa_matriz(n, prod);
    if (!b.empty()) {
        cout << "Checando A^{-1} * b:\n";
        vector<double> vb(n, 0.0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                vb[i] += Inv[i][j] * b[j];
        printa_vetor(vb);
    }
}

void limpa_tela() {
    // limpa a tela do console (funciona na maioria dos terminais)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void menu() {
    cout << "\n--- Menu ---\n";
    cout << "1) Resolver Ax=b por Gauss-Jacobi (mostrar historico)\n";
    cout << "2) Resolver Ax=b por Gauss-Seidel (mostrar historico)\n";
    cout << "3) Calcular A^{-1} por Jacobi\n";
    cout << "4) Calcular A^{-1} por Gauss-Seidel\n";
    cout << "5) Checar A * A^{-1} e A^{-1} * b (se A^{-1} disponivel)\n";
    cout << "6) Calibracao simples: variar b e resolver metodos\n";
    cout << "7) Imprimir A e b\n";
    cout << "0) Sair\n";
    cout << "Escolha: ";
}

void printa_matriz_e_vetor(int n,vector<vector<double>> A, vector<double> b) {

    cout << fixed << setprecision(2);

    for ( int i=0; i<n; i++) {

        // matriz
        i==(int)n/2 ? cout << "A = " : cout << "    ";

        i == 0 ? cout << "┌ ": cout << "│ ";

        for ( int j=0; j<n; j++) {
            cout << A[i][j] << " ";
        }
        // vetor
        i==(int)n/2 ? cout << " │ b = " : cout << " │     ";  
        cout << "│ " << b[i] << " │ " << endl;
    }
}
