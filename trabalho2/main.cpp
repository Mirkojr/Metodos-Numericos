#include "metodos.h"
#include "interface.h"


using namespace std;

int main() {
    
    exibirCabecalhoPrincipal();

    int n;
    double epsilon;
    int iterMax;
    vector<vector<double>> A;
    vector<double> b;

    //Configuração e Entrada de Dados
    lerDadosEntrada(n, A, b, epsilon, iterMax);

    imprimirMatrizEstilizada(n, A, "MATRIZ DO SISTEMA (A)");
    imprimirResultadoVetor("VETOR DO SISTEMA (b)", b);
    cout << endl;

    // Análise de Matrizes Inversas
    vector<DadosIteracao> histInvJ, histInvS;
    vector<vector<double>> invJacobi = calculaInversaJacobi(n, A, epsilon, iterMax, &histInvJ);
    vector<vector<double>> invSeidel = calculaInversaSeidel(n, A, epsilon, iterMax, &histInvS);

    imprimirMatrizEstilizada(n, invJacobi, "MATRIZ INVERSA (GAUSS-JACOBI)");
    cout << endl;
    imprimirMatrizEstilizada(n, invSeidel, "MATRIZ INVERSA (GAUSS-SEIDEL)");

    vector<double> resJacobi = multiplicarMatrixVetor(n, invJacobi, b);
    vector<double> resSeidel = multiplicarMatrixVetor(n, invSeidel, b);

    quadroResultadosVetor(resJacobi, resSeidel);
    cout << endl;
    printa_historico(histInvJ, "Histórico de Cálculo da Inversa - Gauss-Jacobi");
    printa_historico(histInvS, "Histórico de Cálculo da Inversa - Gauss-Seidel");

    // Execução dos Métodos Iterativos
    vector<DadosIteracao> histJ, histS; 
    
    vector<double> solJ = Gauss_Jacobi(n, A, b, epsilon, iterMax, &histJ);
    vector<double> solS = Gauss_Seidel(n, A, b, epsilon, iterMax, &histS);

    // Preparação e exibição do Quadro Resumo
    vector<LinhaSistema> tabela;
    for(int i = 0; i < n; i++) {
        tabela.push_back({"d" + to_string(i+1), solJ[i], solS[i]});
    }

    quadroResumoSistemas(tabela, histJ.back(), histS.back());

    // Análise Final de Segurança
    mostrarAnaliseSismica(n, solS, "Gauss-Seidel");
    mostrarAnaliseSismica(n, solJ, "Gauss-Jacobi");

    // Printa histórico de iterações
    printa_historico(histJ, "Histórico de Iterações - Gauss-Jacobi");
    printa_historico(histS, "Histórico de Iterações - Gauss-Seidel");

    return 0;
}
