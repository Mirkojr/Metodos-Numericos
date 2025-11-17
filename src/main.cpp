#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include "functionParser.h"
#include "metodos.h"

using namespace std;

// --- Estrutura para armazenar resultados ---
struct LinhaSimples {
    double a;
    // Resultado é o tipo que vem da classe Metodos (newtonRaphson, etc.)
    Resultado newton;
    Resultado newtonMod;
    Resultado secante;
};

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
        std::ostringstream fss, dss;
        fss << std::fixed << std::setprecision(6) << a << "*e ^ d - 4*d^2";
        dss << std::fixed << std::setprecision(6) << a << "*e ^ d - 8*d";

        string func = fss.str();
        string funcDerivate = dss.str();

        metodo.setFunc(func);
        metodo.setDerivate(funcDerivate);

        cout << "== Analise para a = " << a << " ==\n";

        // Chama os métodos e armazena os resultados
        Resultado resNewton = metodo.newtonRaphson(d0, epsilon, epsilon, maxIter);
        Resultado resNewtonMod = metodo.newtonRaphsonModificado(d0, epsilon, epsilon, maxIter);
        Resultado resSecante = metodo.secante(d0, d0 + 0.1, epsilon, epsilon, maxIter);

        // Armazena para a tabela final
        tabela.push_back({a, resNewton, resNewtonMod, resSecante});

        // 3. SAÍDA DE RESULTADOS IMEDIATA (Mais simples)
        cout << "  - Newton-Raphson:\tRaiz = " << std::setprecision(6) << resNewton.raiz
             << "\tIter = " << resNewton.iteracoes << "\tErro = " << resNewton.erro << '\n';

        cout << "  - Newton Modificado:\tRaiz = " << std::setprecision(6) << resNewtonMod.raiz
             << "\tIter = " << resNewtonMod.iteracoes << "\tErro = " << resNewtonMod.erro << '\n';

        cout << "  - Secante:\t\tRaiz = " << std::setprecision(6) << resSecante.raiz
             << "\tIter = " << resSecante.iteracoes << "\tErro = " << resSecante.erro << '\n';

        cout << "\n";
    }

    // 4. QUADRO RESUMO 
    cout << "\n=== Quadro Comparativo Resumido ===\n";
    cout << "a\t| Newton (Raiz, Iter)\t| Newton Mod (Raiz, Iter)\t| Secante (Raiz, Iter)\n";
    cout << "-----------------------------------------------------------------------------------\n";

    for (auto& L : tabela) {
        cout << std::fixed << std::setprecision(2) << L.a << "\t| ";

        cout << std::setprecision(6) << L.newton.raiz << ", " << L.newton.iteracoes << "\t| ";
        cout << std::setprecision(6) << L.newtonMod.raiz << ", " << L.newtonMod.iteracoes << "\t\t| ";
        cout << std::setprecision(6) << L.secante.raiz << ", " << L.secante.iteracoes << '\n';
    }
    cout << "-----------------------------------------------------------------------------------\n";

    cout << "\n==== Fim do Calculo ====\n";
    return 0;
}