#include "metodos.h"

using namespace std;

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

void imprime_vetor(const vector<double>& v) {
    cout << "[ ";
    for (double x : v) cout << fixed << setprecision(8) << x << " ";
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
        imprime_vetor(vb);
    }
}

int main() {

    cout << "=== Trabalho: Gauss-Jacobi / Gauss-Seidel - Main ===\n";

    int n;
    cout << "Informe n (numero de deslocamentos, ou 0 para usar exemplo n=3): ";
    cin >> n;

    vector<vector<double>> A;
    vector<double> b;
    if (n == 0) {
        // Matriz/exemplo do enunciado
        n = 3;
        A = vector<vector<double>>(n, vector<double>(n));
        A[0] = {5, 3, 1};
        A[1] = {5, 6, 1};
        A[2] = {1, 6, 7};
        b = {1, 2, 3};
        cout << "Usando matriz exemplo:\n";
        printa_matriz(n, A);
        cout << "b = "; imprime_vetor(b);
    } else {
        A = vector<vector<double>>(n, vector<double>(n, 0.0));
        b = vector<double>(n, 0.0);
        cout << "Deseja digitar A e b manualmente? (1 = sim / 0 = nao (zera tudo)) : ";
        int opt; cin >> opt;
        if (opt == 1) {
            le_matriz(n, A);
            le_vetor(n, b);
        } else {
            cout << "Inicializando A identidade e b = zeros.\n";
            for (int i = 0; i < n; ++i) {
                A[i][i] = 1.0;
                b[i] = 0.0;
            }
        }
    }

    double epsilon;
    int iterMax;
    cout << "Informe epsilon (precisao): ";
    cin >> epsilon;
    cout << "Informe iterMax (limite iteracoes): ";
    cin >> iterMax;

    while (true) {
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
        int escolha;
        cin >> escolha;

        if (escolha == 0) break;

        if (escolha == 1) {
            vector<DadosIteracao> historico;
            vector<vector<double>> copiaA = A;
            vector<double> copiab = b;
            vector<double> sol = Gauss_Jacobi(n, copiaA, copiab, epsilon, iterMax, &historico);
            cout << "Solucao (Jacobi): ";
            imprime_vetor(sol);
            cout << "Historico:\n";
            printa_historico(historico);
        } else if (escolha == 2) {
            vector<DadosIteracao> historico;
            vector<vector<double>> copiaA = A;
            vector<double> copiab = b;
            vector<double> sol = Gauss_Seidel(n, copiaA, copiab, epsilon, iterMax, &historico);
            cout << "Solucao (Gauss-Seidel): ";
            imprime_vetor(sol);
            cout << "Historico:\n";
            printa_historico(historico);
        } else if (escolha == 3) {
            cout << "Calculando inversa por Jacobi (pode demorar)...\n";
            vector<vector<double>> copiaA = A;
            vector<vector<double>> invA = calculaInversaJacobi(n, copiaA, epsilon, iterMax);
            cout << "A^{-1} (Jacobi):\n";
            printa_matriz(n, invA);
        } else if (escolha == 4) {
            cout << "Calculando inversa por Gauss-Seidel (pode demorar)...\n";
            vector<vector<double>> copiaA = A;
            vector<vector<double>> invA = calculaInversaSeidel(n, copiaA, epsilon, iterMax);
            cout << "A^{-1} (Seidel):\n";
            printa_matriz(n, invA);
        } else if (escolha == 5) {
            cout << "Deseja calcular inversa (1 = Jacobi / 2 = Seidel) ou usar inversa ja calculada (0)? ";
            int o; cin >> o;
            if (o == 1) {
                vector<vector<double>> invA = calculaInversaJacobi(n, A, epsilon, iterMax);
                produto_e_imprime(n, A, invA, b);
            } else if (o == 2) {
                vector<vector<double>> invA = calculaInversaSeidel(n, A, epsilon, iterMax);
                produto_e_imprime(n, A, invA, b);
            } else {
                cout << "Nenhuma inversa fornecida.\n";
            }
        } else if (escolha == 6) {
            cout << "Calibracao simples: vamos variar b adicionando pequenos desvios e resolver ambos metodos.\n";
            for (int t = -2; t <= 2; ++t) {
                vector<double> b_var = b;
                for (int i = 0; i < n; ++i) b_var[i] += 0.1 * t * (i+1);
                cout << "\nVariação t=" << t << " -> b = "; imprime_vetor(b_var);

                vector<DadosIteracao> hJ, hS;
                vector<vector<double>> A1 = A;
                vector<double> solJ = Gauss_Jacobi(n, A1, b_var, epsilon, iterMax, &hJ);
                vector<vector<double>> A2 = A;
                vector<double> solS = Gauss_Seidel(n, A2, b_var, epsilon, iterMax, &hS);

                cout << "Jacobi sol: "; imprime_vetor(solJ);
                cout << "Seidel sol: "; imprime_vetor(solS);
            }
            cout << "Calibracao concluida.\n";
        } else if (escolha == 7) {
            cout << "A:\n"; printa_matriz(n, A);
            cout << "b: "; imprime_vetor(b);
        } else {
            cout << "Opcao invalida.\n";
        }
    }

    cout << "Encerrando.\n";
    return 0;
}
