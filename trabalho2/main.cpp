#include "metodos.h"

int main() {
    // Exemplo de entrada baseado nos slides [6]
    int n = 3;
    vector<vector<double>> A = {
        {10, 2, 2},
        {1, 10, 2},
        {2, -7, -10}
    };
    vector<double> b = {28, 7, -17};

    printa_matriz(n, A);                        // Chamada de exemplo para a função printa_matriz
    printa_matriz(n, calcula_inversa(n, A));    // Chamada de exemplo para a função printa_matriz

    return 0;
}
