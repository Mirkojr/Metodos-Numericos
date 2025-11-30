#include "functionParser.h"
#include "metodos.h"

int main() {

    cout << "==== Sistema de Calculo de Deslocamento Simples ====\n\n";

    Metodos metodo("");
    int n;
    double epsilon;
    const int maxIter = 100;

    // 1. ENTRADA DE DADOS
    cout << "Quantos valores de 'a' voce vai testar? ";
    cin >> n;

    vector<double> valoresA(n);
    for (int i = 0; i < n; ++i) {
        cout << "Informe o valor de a[" << i << "]: ";
        cin >> valoresA[i];
    }

    cout << "Qual a precisao (epsilon) desejada? ";
    cin >> epsilon;

    double d0 = 0.5; // Chute inicial fixo

    cout << "\n--- Processando (d0 = " << d0 << ") ---\n\n";

    vector<LinhaSimples> tabela;
    tabela.reserve(n);

    // 2. LOOP DE CÁLCULO PARA CADA 'a'
    for (int i = 0; i < n; ++i) {
        double a = valoresA[i];

        // Monta as strings das funções f(d) e f'(d) 
        // f(d) = a*e^d - 4*d^2
        // f'(d) = a*e^d - 8*d
        ostringstream fss, dss;
        fss << setprecision(6) << a << "*e ^ d - 4*d^2";
        dss << setprecision(6) << a << "*e ^ d - 8*d";

        string func = fss.str();
        string funcDerivate = dss.str();

        metodo.setFunc(func);
        metodo.setDerivate(funcDerivate);

        cout << fixed << setprecision(2) << "== Analise para a = " << a << " ==\n";

        // Chama os métodos e armazena os resultados
        Resultado resNewton = metodo.newtonRaphson(d0, epsilon, epsilon, maxIter);
        Resultado resNewtonMod = metodo.newtonRaphsonModificado(d0, epsilon, epsilon, maxIter);
        Resultado resSecante = metodo.secante(d0, d0 + 0.1, epsilon, epsilon, maxIter);

        // Armazena para a tabela final
        tabela.push_back({a, resNewton, resNewtonMod, resSecante});
    }
    
    // 3. QUADRO RESUMO
    metodo.quadroResumo(tabela);

    return 0;
}
