#include "metodos.h"

int main() {

    int n;
    cout << "Informe n (numero de deslocamentos, ou 0 para usar exemplo n=3): ";
    cin >> n;

    vector<vector<double>> A;
    vector<double> b;
    if (n == 0) {
        // Matriz e vetor exemplo do enunciado
        n = 3;
        A = vector<vector<double>>(n, vector<double>(n));
        A = { {5, 3, 1},
              {5, 6, 1},
              {1, 6, 7} };
        b = {1, 2, 3};
        cout << "Usando matriz exemplo:\n";
        printa_matriz(n, A);
        cout << "b = "; printa_vetor(b);
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
        menu();
        int escolha;
        cin >> escolha;

        limpa_tela();

        switch ( escolha ) {
            case 1: {
                vector<DadosIteracao> historico;
                vector<vector<double>> copiaA = A;
                vector<double> copiab = b;
                vector<double> sol = Gauss_Jacobi(n, copiaA, copiab, epsilon, iterMax, &historico);
                cout << "Historico:\n";
                printa_historico(historico);
                cout << "Solucao (Jacobi): ";
                printa_vetor(sol);
                break;
            }            
            case 2: {
                vector<DadosIteracao> historico;
                vector<vector<double>> copiaA = A;
                vector<double> copiab = b;
                vector<double> sol = Gauss_Seidel(n, copiaA, copiab, epsilon, iterMax, &historico);
                cout << "Historico:\n";
                printa_historico(historico);
                cout << "Solucao (Gauss-Seidel): ";
                printa_vetor(sol);
                break;
            }
            case 3: {
                cout << "Calculando inversa por Jacobi (pode demorar)...\n";
                vector<vector<double>> copiaA = A;
                vector<vector<double>> invA = calculaInversaJacobi(n, copiaA, epsilon, iterMax);
                cout << "A^{-1} (Jacobi):\n";
                printa_matriz(n, invA);
                break;
            }
            case 4: {
                cout << "Calculando inversa por Gauss-Seidel (pode demorar)...\n";
                vector<vector<double>> copiaA = A;
                vector<vector<double>> invA = calculaInversaSeidel(n, copiaA, epsilon, iterMax);
                cout << "A^{-1} (Seidel):\n";
                printa_matriz(n, invA);
                break;
            }
            case 5: {
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
                break;
            }
            case 6: {
                cout << "Calibracao simples: vamos variar b adicionando pequenos desvios e resolver ambos os métodos.\n";
                for (int t = -2; t <= 2; ++t) {
                    vector<double> b_var = b;
                    for (int i = 0; i < n; ++i) b_var[i] += 0.1 * t * (i+1);
                    cout << "\nVariação t=" << t << " -> b = "; printa_vetor(b_var);

                    vector<DadosIteracao> hJ, hS;
                    vector<vector<double>> A1 = A;
                    vector<double> solJ = Gauss_Jacobi(n, A1, b_var, epsilon, iterMax, &hJ);
                    vector<vector<double>> A2 = A;
                    vector<double> solS = Gauss_Seidel(n, A2, b_var, epsilon, iterMax, &hS);

                    cout << "Jacobi sol: "; printa_vetor(solJ);
                    cout << "Seidel sol: "; printa_vetor(solS);
                }
                cout << "Calibracao concluida.\n";
                break;
            }
            case 7: {
                cout << "A:\n"; printa_matriz(n, A);
                cout << "b: "; printa_vetor(b);
                break;
            }
            case 0:
                cout << "Encerrando.\n";
                exit(0);
                break;
            default:
                cout << "Opcao invalida.\n";
        }
    }

    return 0;
}
