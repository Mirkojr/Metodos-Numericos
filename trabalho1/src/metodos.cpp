#include "metodos.h"

Metodos::Metodos(const string& func){
    this->func = func;
}

void Metodos::setFunc(string func){
    this->func = func;
}

void Metodos::setPhi(string phi){
    this->phiFunc = phi;
}

void Metodos::setDerivate(string derivate){
    this->derivate = derivate;
}

void Metodos::printFunc(){
    cout << this->func << endl;
}

double Metodos::F(double x){
    return this->fParser.parse(this->func, x);
}

double Metodos::Phi(double x){
    return this->fParser.parse(this->phiFunc, x);
}

double Metodos::D(double x){
    return this->fParser.parse(this->derivate, x);
}

double Metodos::bissecao( double a, double b, double epslon, int maxIter){
    double Fa = F(a);
    double Fb = F(b);

    cout << Fa << endl;
    cout << Fb << endl;

    if (Fa * Fb > 0){
        cout << "Erro: A função não troca de sinal entre a e b." << endl;
        return NAN;
    }

    double intervX = abs(b-a);
    int k = 0;
    double x;
    while(true){
        x = (a+b)/2; 
        double Fx = F(x);

        if(intervX <= epslon || k >= maxIter) break;
        if(Fa*Fx > 0){
            a = x;
            Fa = Fx;
        }
        else{
            b = x;
            Fb = Fx;
        }
        intervX = intervX/2;
        k++;
    }   
    return x;
}

double Metodos::choose(double a, double b) {
    return (abs(F(a)) < abs(F(b))) ? a : b;
}

double Metodos::posicaoFalsa(double a, double b, double epsilon1, double epsilon2, int maxIter){
    double root;

    double Fa = F(a);
    double Fb = F(b);

    cout << "Fa: " << Fa << endl;
    cout << "Fb: " << Fb << endl;

    if (Fa * Fb > 0){
        cout << "Erro: A função não troca de sinal entre a e b." << endl;
        return NAN;
    }

    double intervX = abs(b-a);
    if(intervX < epsilon1) return choose(a,b);
    if(abs(F(a)) < epsilon2) return a;
    if(abs(F(b)) < epsilon2) return b;
    
    int k = 0;
    double x; double Fx;
    while(true){
        x = (a*F(b) - b*(F(a)))/(F(b)-F(a));
        Fx = F(x);

        if((abs(Fx) < epsilon2) || (k>=maxIter)){
            root = x;
            break;
        }
        if(Fa*Fx > 0){
            a = x;
            Fa = Fx;
        }
        else{
            b = x;
            Fb = Fx;
        }

        intervX = abs(b-a);

        if(intervX <= epsilon1){
            root = choose(a,b);
            break;
        }

        k++;
    }
    
    return root;
}

double Metodos::pontoFixo(double x0, double epsilon1, double epsilon2, int maxIter){

    // checa se Phi foi definida ** obrigatorio **
    if (this->phiFunc.empty()) return (cerr << "Erro: É necessário definir uma phi para calcular ponto fixo" << endl, NAN);

    if(abs(F(x0)) < epsilon1) return x0;

    int k = 1;
    while(true){
        double x1 = Phi(x0);
        if(abs(F(x1)) < epsilon1 || abs(x1-x0) < epsilon2 || k >= maxIter) return x1;
        x0 = x1;
        k++;
    }
}

 Resultado Metodos::newtonRaphson(double x0, double epsilon1, double epsilon2, int maxIter){
    
    if(this->derivate.empty()){
        cerr << "Erro: É necessário definir uma derivada para calcular Newton-Raphson" << endl;
        return {NAN, 0, NAN, ""};
    }

    if(abs(F(x0)) < epsilon1) return {x0, 0, 0.0, ""};

    int k = 1;
    double x1;

    // tabela de iteracoes
    cout << "╭───────────────────────────────────────────────────────╮" << endl;
    cout << "│                     NEWTON-RAPHSON                    │" << endl;
    cout << "├────┬───────────────────┬───────────────┬──────────────┤" << endl;
    cout << "│ k  │ x                 │ f(x)          │ erro         │" << endl;
    cout << "├────┼───────────────────┼───────────────┼──────────────┤\n";


    while(true){
        x1 = x0 - F(x0)/D(x0);
        double erro = abs(x1 - x0);

        // tabela de iteracoes
        cout << "│ "
         << setw(2) << right << k << " │ "
         << setw(17) << left  << scientific << setprecision(6) << x1 << " │ "
         << setw(13) << left  << scientific << setprecision(6) << F(x1) << " │ "
         << setw(12) << left  << scientific << setprecision(6) << erro << " │"
         << endl;

        // printar a linha final da tabela
        if(abs(F(x1)) < epsilon1 || erro < epsilon2 || k >= maxIter) cout << "╰────┴───────────────────┴───────────────┴──────────────╯" << endl;

        if (abs(F(x1)) < epsilon1) return {x1, k, erro, "|f(x)| < epsilon"};
        if (erro < epsilon2)       return {x1, k, erro, "erro < epsilon"};
        if (k >= maxIter)          return {x1, k, erro, "k >= maxIter"};

        x0 = x1;
        k++;
    }
 }

 Resultado Metodos::secante(double x0, double x1, double epsilon1, double epsilon2, int maxIter){
    if(abs(F(x0)) < epsilon1) return {x0, 0, 0.0, ""};
    if(abs(F(x1)) < epsilon1 || abs(x1-x0) < epsilon2) return {x1, 0, abs(x1-x0), ""};

    double x2;
    int k = 1;

    // tabela de iteracoes
    cout << "╭───────────────────────────────────────────────────────╮" << endl;
    cout << "│                        SECANTE                        │" << endl;
    cout << "├────┬───────────────────┬───────────────┬──────────────┤" << endl;
    cout << "│ k  │ x                 │ f(x)          │ erro         │" << endl;
    cout << "├────┼───────────────────┼───────────────┼──────────────┤\n";

    while(true){
        x2 = x1 - (F(x1)/(F(x1)-F(x0)) * (x1-x0));
        double erro = abs(x2 - x1);

        // tabela de iteracoes
        cout << "│ "
         << setw(2) << right << k << " │ "
         << setw(17) << left  << scientific << setprecision(6) << x1 << " │ "
         << setw(13) << left  << scientific << setprecision(6) << F(x1) << " │ "
         << setw(12) << left  << scientific << setprecision(6) << erro << " │"
         << endl;

        // printar a linha final da tabela
        if(abs(F(x2)) < epsilon1 || erro < epsilon2 || k >= maxIter) cout << "╰────┴───────────────────┴───────────────┴──────────────╯" << endl;

        if (abs(F(x2)) < epsilon1) return {x2, k, erro, "|f(x)| < epsilon"};
        if (erro < epsilon2)       return {x2, k, erro, "erro < epsilon"};
        if (k >= maxIter)          return {x2, k, erro, "k >= maxIter"};

        x0 = x1;
        x1 = x2;
        k++;
    }
 }

Resultado Metodos::newtonRaphsonModificado(double x0, double epsilon1, double epsilon2, int maxIter) {
    
    if (this->derivate.empty()){
        cerr << "Erro: É necessário definir uma derivada para calcular Newton Modificado" << endl;

        return {NAN, 0, NAN, ""};
    }

    // calcula a derivada apenas uma vez (fixa)
    double d0 = D(x0);
    if (d0 == 0){
        cerr << "Erro: f'(x0) = 0 em Newton Modificado" << endl;
        return {NAN, 0, NAN, ""};
    }

    // teste inicial
    if (abs(F(x0)) < epsilon1){
        return {x0, 0, 0.0, ""};
    }

    int k = 1;
    double x1;

    // tabela de iteracoes
    cout << "╭───────────────────────────────────────────────────────╮" << endl;
    cout << "│                   NEWTON-MODIFICADO                   │" << endl;
    cout << "├────┬───────────────────┬───────────────┬──────────────┤" << endl;
    cout << "│ k  │ x                 │ f(x)          │ erro         │" << endl;
    cout << "├────┼───────────────────┼───────────────┼──────────────┤" << endl;

    while (true) {

        // evitar explosão numérica
        if (isnan(x0) || isinf(x0) || x0 > 1e6 || x0 < -1e6) {
            cerr << "Divergência numérica detectada." << endl;
            return {NAN, k, NAN, ""};
        }

        // usa a derivada fixa d0
        x1 = x0 - F(x0) / d0;

        // evitar explosão ao calcular x1
        if (isnan(x1) || isinf(x1)) {
            cerr << "Divergência: x1 inválido." << endl;
            return {NAN, k, NAN, ""};
        }

        double erro = abs(x1 - x0);

        // tabela de iteracoes
        cout << "│ "
         << setw(2) << right << k << " │ "
         << setw(17) << left  << scientific << setprecision(6) << x1 << " │ "
         << setw(13) << left  << scientific << setprecision(6) << F(x1) << " │ "
         << setw(12) << left  << scientific << setprecision(6) << erro << " │"
         << endl;

        // printar a linha final da tabela
        if (abs(F(x1)) < epsilon1 || erro < epsilon2 || k >= maxIter) cout << "╰────┴───────────────────┴───────────────┴──────────────╯" << endl;

        if (abs(F(x1)) < epsilon1) return {x1, k, erro, "|f(x)| < epsilon"};
        if (erro < epsilon2)       return {x1, k, erro, "erro < epsilon"};
        if (k >= maxIter)          return {x1, k, erro, "k >= maxIter"};

        x0 = x1;
        k++;
    }
}

// QUADRO RESUMO
// quadro estilo tabela (q so funciona no linux)
void Metodos::quadroResumo(vector<LinhaSimples> tabela) {
    cout << "╭────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╮\n";
    cout << "│                                                   Quadro Comparativo Resumido                                                  │\n";
    cout << "├───────┬───────────────────────────────────────┬───────────────────────────────────────┬────────────────────────────────────────┤\n";
    cout << "│ a     │ Newton (Raiz, Iter, Parada)           │ Newton Mod (Raiz, Iter, Parada)       │ Secante (Raiz, Iter, Parada)           │\n";
    cout << "├───────┼───────────────────────────────────────┼───────────────────────────────────────┼────────────────────────────────────────┤\n";
    for (auto& L : tabela) {
        cout << fixed << setprecision(2) << "│ " << L.a << "\t│ ";
        
        cout << scientific << setprecision(6) << L.newton.raiz    << ", " << L.newton.iteracoes    << ", " << L.newton.parada << "\t│ ";
        cout << scientific << setprecision(6) << L.newtonMod.raiz << ", " << L.newtonMod.iteracoes << ", " << L.newtonMod.parada << "\t│ ";
        cout << scientific << setprecision(6) << L.secante.raiz   << ", " << L.secante.iteracoes   << ", " << L.secante.parada << "\t │\n";
    }
    cout << "╰───────┴───────────────────────────────────────┴───────────────────────────────────────┴────────────────────────────────────────╯\n";
}
