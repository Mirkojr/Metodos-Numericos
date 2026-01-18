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

void mostrarAnaliseSismica(int n, const vector<double>& deslocamentos, string titulo) {
    const int LARGURA_TOTAL = 90;
    const int ESPACO_INTERNO = LARGURA_TOTAL - 3;

    string textoTopo = " ANÁLISE DE INTEGRIDADE SÍSMICA (" + titulo + ") ";
    int hifens = (LARGURA_TOTAL - 2 - textoTopo.length()) / 2;
    
    cout << "\n╭";
    imprimirRepetido("─", hifens);
    cout << textoTopo;
    imprimirRepetido("─", LARGURA_TOTAL - 2 - hifens - textoTopo.length());
    cout << "╮" << endl;

    bool perigo = false;
    for (int i = 0; i < n; i++) {
        if (abs(deslocamentos[i]) > 0.4) { 
            stringstream ss;
            ss << "[ALERTA] Deslocamento d" << i+1 
               << " (" << fixed << setprecision(6) << deslocamentos[i] << " cm) excede o limite!";

            cout << "│ " << left << setw(ESPACO_INTERNO - 2) << ss.str() << "│" << endl;
            perigo = true;
        }
    }

    if (!perigo) {
        cout << "│ " << left << setw(ESPACO_INTERNO) << "[OK] Todos os deslocamentos estão dentro da zona de segurança." << "│" << endl;
    }

    cout << "╰"; imprimirRepetido("─", LARGURA_TOTAL - 4); cout << "╯" << endl;
}

void printa_historico(const vector<DadosIteracao>& h, string titulo) {
    if (h.empty()) return;

    // Cabeçalho
    cout << "\n╭──────┬──────────────┬──────────────────────────────────────────────────────╮" << endl;

    // Calcula o tamanho VISUAL da string (ignorando bytes extras de acentos UTF-8)
    int tamanho_visual = 0;
    for (unsigned char c : titulo) {
        if ((c & 0xC0) != 0x80) tamanho_visual++;
    }

    // A largura interna total é 74. Calculamos quanto falta preencher.
    int espacos_restantes = 74 - tamanho_visual;

    // Imprime
    cout << "│ " << titulo;
    for (int i = 0; i < espacos_restantes; i++) cout << " "; 
    cout << " │" << endl;
    cout << "├──────┼──────────────┼──────────────────────────────────────────────────────┤" << endl;
    cout << "│  k   │    Norma     │                 Vetor Solução (x)                    │" << endl;
    cout << "├──────┼──────────────┼──────────────────────────────────────────────────────┤" << endl;

    for (const auto& reg : h) {
        // Imprime k e Norma
        cout << "│ " << setw(4) << right << reg.k << " │ ";
        cout << scientific << setprecision(4) << setw(12) << reg.norma << " │ ";

        // Monta o Vetor Alinhado
        stringstream ss;
        ss << "[ "; 
        for (size_t i = 0; i < reg.x.size(); ++i) {

            // Isso alinha os sinais de menos e as vírgulas.
            ss << fixed << setw(8) << setprecision(4) << reg.x[i];
            
            // Adiciona a vírgula apenas se não for o último
            ss << (i == reg.x.size() - 1 ? "" : ", ");
        }
        ss << " ]";

        // Imprime o vetor montado preenchendo o resto da tabela com espaços
        cout << left << setw(52) << ss.str() << " │" << endl;
    }

    cout << "╰──────┴──────────────┴──────────────────────────────────────────────────────╯" << endl;
}


void imprimirResultadoVetor(const string& rotulo, const vector<double>& v) {
    stringstream ss;
    ss << "➤ " << rotulo << ": [ ";
    for (size_t i = 0; i < v.size(); i++) {
        ss << fixed << setprecision(6) << v[i] << (i == v.size() - 1 ? "" : ", ");
    }
    ss << " ]";

    cout << "│ " << left << setw(68) << ss.str() << " │" << endl;
}

void quadroResultadosVetor(const vector<double>& resJacobi, const vector<double>& resSeidel) {
    cout << "\n╭────────────────────────────────────────────────────────────────────╮" << endl;
    cout << "│               RESULTADO: MATRIZ INVERSA * VETOR B                  │" << endl;
    cout << "├────────────────────────────────────────────────────────────────────┤" << endl;

    imprimirResultadoVetor("Resultado (Jacobi)", resJacobi);
    imprimirResultadoVetor("Resultado (Seidel)", resSeidel);

    cout << "╰────────────────────────────────────────────────────────────────────╯" << endl;
}