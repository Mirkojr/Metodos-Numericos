#include "functionParser.h"
#include "metodos.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {

    cout << "==== Sistema de Calculo de Deslocamento Sismico ====\n\n";

    int n;
    double epsilon;

    // Entrada do número de valores de a
    cout << "Informe o numero de valores de a: ";
    cin >> n;

    vector<double> valoresA(n);

    // Entradas dos valores de a
    for (int i = 0; i < n; i++) {
        cout << "Informe o valor de a[" << i << "]: ";
        cin >> valoresA[i];
    }

    // Entrada da precisão
    cout << "Informe o valor da precisao e: ";
    cin >> epsilon;

    // Aproximação inicial padrão
    double d0 = 0.5;

    // Aqui serão feitos os cálculos para cada método
    cout << "\nProcessando...\n\n";

    // LOOP para cada valor de a
    for (int i = 0; i < n; i++) {

        double a = valoresA[i];

        cout << "=== Valor a = " << a << " ===\n";

        // (a) Newton-Raphson (A IMPLEMENTAR)
        // double d_newton = newton(a, d0, epsilon);

        // (b) Newton Modificado (A IMPLEMENTAR)
        // double d_newton_mod = newton_mod(a, d0, epsilon);

        // (c) Secante (A IMPLEMENTAR)
        // double d_secante = secante(a, d0, epsilon);

        // (e) Mostrar quadro resposta (A IMPLEMENTAR)
        // printQuadroResposta(...);

        cout << endl;
    }

    // (f) Mostrar quadro comparativo geral (A IMPLEMENTAR)
    // printQuadroComparativo(...);

    // (g) Análise da variação de a (A IMPLEMENTAR)
    // analisarVariacaoA(...);

    return 0;
}
