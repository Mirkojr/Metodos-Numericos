#include "metodos.h"

int main() {
    
    // =============================================================
    // ITEM C: Calibrar o sistema usando A e b dados
    // =============================================================
    int n = 3;
    
    // Matriz A do problema (Ondas sísmicas)
    vector<vector<double>> A = {
        {5, 3, 1},
        {5, 6, 1},
        {1, 6, 7}
    };
    
    // Vetor b (Termos independentes)
    vector<double> b = {1, 2, 3};

    // Parâmetros de precisão
    double epsilon = 0.0001;
    int iterMax = 100;

    cout << fixed << setprecision(5);
    cout << "===========================================================" << endl;
    cout << "     ANALISE DE ESTRUTURA - ONDAS SISMICAS (n=" << n << ")" << endl;
    cout << "===========================================================" << endl;

    // =============================================================
    // ITEM A: Calcular Inversa e {d} por Gauss-Jacobi
    // =============================================================
    cout << "\n--- [ITEM A] Metodo de Gauss-Jacobi ---" << endl;
    
    vector<vector<double>> Inv_Jacobi = calculaInversaJacobi(n, A, epsilon, iterMax);
    vector<double> d_Jacobi = multiplicarMatrixVetor(n, Inv_Jacobi, b);

    cout << "Matriz Inversa (Jacobi):" << endl;
    printa_matriz(n, Inv_Jacobi);
    
    cout << "\nVetor Deslocamento {d} (Jacobi):" << endl;
    cout << "[ ";
    for(double val : d_Jacobi) cout << val << " ";
    cout << "]" << endl;

    // =============================================================
    // ITEM B: Calcular Inversa e {d} por Gauss-Seidel
    // =============================================================
    cout << "\n--- [ITEM B] Metodo de Gauss-Seidel ---" << endl;

    vector<vector<double>> Inv_Seidel = calculaInversaSeidel(n, A, epsilon, iterMax);
    vector<double> d_Seidel = multiplicarMatrixVetor(n, Inv_Seidel, b);

    cout << "Matriz Inversa (Seidel):" << endl;
    printa_matriz(n, Inv_Seidel);

    cout << "\nVetor Deslocamento {d} (Seidel):" << endl;
    cout << "[ ";
    for(double val : d_Seidel) cout << val << " ";
    cout << "]" << endl;

    // =============================================================
    // ITEM D: Quadro Resposta Comparativo
    // =============================================================
    cout << "\n===========================================================" << endl;
    cout << "--- [ITEM D] Quadro Resposta ---" << endl;
    cout << "Var   |  Valor (Jacobi)  |  Valor (Seidel)" << endl;
    cout << "------------------------------------------" << endl;
    for(int i = 0; i < n; i++) {
        cout << "d" << (i+1) << "    |   " << setw(10) << d_Jacobi[i] << "     |   " << setw(10) << d_Seidel[i] << endl;
    }

    // =============================================================
    // ITEM E: Analise de Risco (Limite de 0.4 cm)
    // =============================================================
    cout << "\n===========================================================" << endl;
    cout << "--- [ITEM E] Analise de Seguranca ---" << endl;
    
    bool perigo = false;
    // Vamos usar o resultado de Seidel para análise (geralmente converge mais rápido/estável)
    // Mas poderia usar Jacobi também, já que devem dar resultados próximos.
    vector<double>& d_final = d_Seidel; 

    cout << "Criterio de Seguranca: Modulo do deslocamento < 0.4 cm" << endl;
    
    for(int i = 0; i < n; i++) {
        double valor_abs = abs(d_final[i]);
        cout << "Deslocamento d" << (i+1) << " = " << d_final[i] << " cm -> |" << valor_abs << "| ";
        
        if (valor_abs > 0.4) {
            cout << "[ALERTA: ACIMA DO LIMITE]" << endl;
            perigo = true;
        } else {
            cout << "[OK]" << endl;
        }
    }

    cout << "\nCONCLUSAO FINAL:" << endl;
    if (perigo) {
        cout << ">>> PERIGO: Podem ocorrer serios danos e um problema gigantesco na estrutura. <<<" << endl;
    } else {
        cout << ">>> SEGURO: A estrutura suportara as ondas sismicas. <<<" << endl;
    }

    return 0;
}
