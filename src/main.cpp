#include "functionParser.h"
#include "metodos.h"
#include <iostream>
#include <vector>

using namespace std;

void testMethods(){
    Metodos metodo("x^3 - x - 2");
    metodo.setDerivate("3*x^2 - 1");

    double a = 1.0;
    double b = 2.0;
    double epsilon1 = 1e-6;
    double epsilon2 = 1e-6;
    int maxIter = 100;

    Resultado resNewton = metodo.newtonRaphson(1.5, epsilon1, epsilon2, maxIter);
    cout << "Newton-Raphson: Raiz = " << resNewton.raiz << ", Iteracoes = " << resNewton.iteracoes << ", Erro = " << resNewton.erro << endl;

    Resultado resSecante = metodo.secante(1.0, 2.0, epsilon1, epsilon2, maxIter);
    cout << "Secante: Raiz = " << resSecante.raiz << ", Iteracoes = " << resSecante.iteracoes << ", Erro = " << resSecante.erro << endl;

    Resultado resNewtonMod = metodo.newtonRaphsonModificado(1.5, epsilon1, epsilon2, maxIter);
    cout << "Newton-Raphson Modificado: Raiz = " << resNewtonMod.raiz << ", Iteracoes = " << resNewtonMod.iteracoes << ", Erro = " << resNewtonMod.erro << endl;

    cout << "----------------------------------" << endl;
}

void testParser(){
    FunctionParser parser;

    auto test = [&](string func, char var, double val){
        double r = parser.parse(func, var, val);
        cout << "Func: " << func 
             << " | var=" << var 
             << " | val=" << val 
             << " | result=" << r << endl;
    };

    cout << "\n===== TESTES DO PARSER =====\n";

    // Teste básico do usuário
    test("3 - (-2)", 'x', 2.0);           // esperado: 5

    // Negativos em multiplicação
    test("3 * (-2)", 'x', 0);            // esperado: -6
    test("(-3) * (-2)", 'x', 0);         // esperado: 6
    test("-(3*2)", 'x', 0);              // esperado: -6

    // Somatório
    test("1 + 2 + 3 + 4", 'x', 0);       // esperado: 10

    // Mistura com divisão
    test("10 / (2 + 3)", 'x', 0);        // esperado: 2

    // Potenciação
    test("2^3", 'x', 0);                 // esperado: 8
    test("2^(3+1)", 'x', 0);             // esperado: 16
    test("(-2)^3", 'x', 0);              // esperado: -8

    // Expressões aninhadas
    test("3*(2 + 5) - 4/2", 'x', 0);     // esperado: 19

    // Teste com variáveis
    test("x + 3", 'x', 10);              // esperado: 13
    test("2*x + 1", 'x', 4);             // esperado: 9
    test("3*(x - 2)", 'x', 5);           // esperado: 9

    // Expressões mistas com variável negativa
    test("3 * (x - (-2))", 'x', -4);     // esperado: 3 * (-4 + 2) = 3 * (-2) = -6

    // Euler
    test("e", 'x', 0);                   // esperado: exp(1)
    test("2*e", 'x', 0);                 // esperado: 2*exp(1)
    test("e + 1", 'x', 0);               // esperado: exp(1)+1

    // Mais combinações
    test("-(x)", 'x', 6);                // esperado: -6
    test("-(-x)", 'x', 6);               // esperado: 6
    test("(-x) * 3", 'x', 5);            // esperado: -15
    test("3 + -(2)", 'x', 0);            // esperado: 1
    test("3 + -2", 'x', 0);              // esperado: 1

    // Avaliação mais longa
    test("10 - (2 + 3*4) + (-2)", 'x', 0);  // esperado: 10 - (2+12) -2 = -6

    double value = parser.parse("x+3");
    cout << value << endl;
    cout << "===== FIM DOS TESTES =====\n";
}


int main() {

    //testMethods();
    testParser();
    return 0;
}
