#include "interface.h"
#include <sstream>

// Funções auxiliares internas
void imprimirRepetido(string s, int n) {
    for (int i = 0; i < n; i++) cout << s;
}

void exibirCabecalhoPrincipal() {
    cout << "╭────────────────────────────────────────────────────────────────────────────────╮" << endl;
    cout << "│                SISTEMA DE ANÁLISE DE DESLOCAMENTOS SÍSMICOS                    │" << endl;
    cout << "╰────────────────────────────────────────────────────────────────────────────────╯" << endl;
}

void lerDadosEntrada(int& n, vector<vector<double>>& A, vector<double>& b, double& epsilon, int& iterMax) {
    cout << "  ➤ Informe n (deslocamentos) ou 0 para Calibração Padrão: ";
    cin >> n;

    if (n == 0) {
        n = 3;
        A = {{5, 3, 1}, {5, 6, 1}, {1, 6, 7}}; // Matriz de calibração padrão
        b = {1, 2, 3};
        cout << "  [!] Usando Matriz e Vetor de Calibração do Enunciado.\n";
    } else {
        A.assign(n, vector<double>(n));
        b.assign(n, 0.0);
        
        cout << "  ➤ Preencha a Matriz A (" << n << "x" << n << "):\n";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cin >> A[i][j];
            }
        }
        
        cout << "  ➤ Preencha o Vetor b:\n";
        for(int i = 0; i < n; i++) {
            cin >> b[i];
        }
    }

    cout << "  ➤ Precisão (epsilon): "; cin >> epsilon;
    cout << "  ➤ Limite de iterações: "; cin >> iterMax;
}

// para impressao das inversas
void imprimirMatrizEstilizada(int n, const vector<vector<double>>& M, string titulo) {
    cout << "╭"; imprimirRepetido("─", titulo.length() + 2); cout << "╮" << endl;
    cout << "│ " << titulo << " │" << endl;
    cout << "├"; imprimirRepetido("─", (n * 15)); cout << "─╮" << endl;

    for (int i = 0; i < n; i++) {
        cout << "│ ";
        for (int j = 0; j < n; j++) {
            cout << setw(14) << fixed << setprecision(6) << M[i][j] << " ";
        }
        cout << "│" << endl;
    }
    cout << "╰"; imprimirRepetido("─", (n * 15)); cout << "─╯" << endl;
}

void quadroResumoSistemas(const vector<LinhaSistema>& tabela, DadosIteracao ultimoJ, DadosIteracao ultimoS) {
    // Definimos as larguras exatas das colunas (devem somar o total da moldura)
    const int W_VAR = 10;
    const int W_JAC = 40;
    const int W_SEI = 44;

    cout << "\n╭────────────────────────────────────────────────────────────────────────────────────────────────╮" << endl;
    cout << "│                                  QUADRO COMPARATIVO DE MÉTODOS                                 │" << endl;
    cout << "├──────────┬────────────────────────────────────────┬────────────────────────────────────────────┤" << endl;
    cout << "│ " << left << setw(W_VAR-2) << "Variável" 
         << " │ " << setw(W_JAC-2) << "Gauss-Jacobi (Valor Final)" 
         << " │ " << setw(W_SEI-2) << "Gauss-Seidel (Valor Final)" << " │" << endl;
    cout << "├──────────┼────────────────────────────────────────┼────────────────────────────────────────────┤" << endl;

    for (const auto& linha : tabela) {
        cout << "│ " << left << setw(W_VAR-2) << linha.id 
             << " │ " << setw(W_JAC-2) << fixed << setprecision(8) << linha.valJacobi 
             << " │ " << setw(W_SEI-2) << linha.valSeidel << " │" << endl;
    }

    cout << "├──────────┼────────────────────────────────────────┼────────────────────────────────────────────┤" << endl;

    ostringstream ssJ, ssS;
    ssJ << "Iteraç.: " << ultimoJ.k << " | Norma:  " << scientific << setprecision(4) << ultimoJ.norma;
    ssS << "Iteraç.: " << ultimoS.k << " | Norma:  " << scientific << setprecision(4) << ultimoS.norma;

    cout << "│ " << left << setw(W_VAR-1) << "Info"  
         << "│ " << setw(W_JAC-1) << ssJ.str() 
         << " │ " << setw(W_SEI-1) << ssS.str() << " │" << endl;
    
    cout << "╰──────────┴────────────────────────────────────────┴────────────────────────────────────────────╯" << endl;
}

void mostrarAnaliseSismica(int n, const vector<double>& deslocamentos) {
    cout << "\n╭────────────────── ANÁLISE DE INTEGRIDADE SÍSMICA ──────────────────╮" << endl;
    bool perigo = false;
    for (int i = 0; i < n; i++) {
        if (abs(deslocamentos[i]) > 0.4) { 
            stringstream ss;
            ss << "[ALERTA] Deslocamento d" << i+1 
            << " (" << fixed << setprecision(6) << deslocamentos[i] << " cm) excede o limite!";

            cout << "│ " << left << setw(67) << ss.str() << "│" << endl;
            
            perigo = true;
        }
    }
    if(!perigo) cout << "│ [OK] Todos os deslocamentos estão dentro da zona de segurança.     │" << endl;
    cout << "╰────────────────────────────────────────────────────────────────────╯" << endl;
}