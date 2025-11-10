#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "functionParser.h"

using namespace std;

// --- Substitui variável e 'e' de forma segura (constrói uma nova string) ---
string FunctionParser::variableToValue(string function, char variable, double value){
    string result;
    result.reserve(function.size() + 32);

    // Formata value sem zeros extras e com sinal
    std::ostringstream oss;
    oss << std::setprecision(12) << value;
    string valueStr = oss.str();
    if (value < 0 && valueStr.front() != '(') valueStr = "(" + valueStr + ")";

    // Agora 'e' vira diretamente a constante 
    const string eulerText = "2.718281828459045";

    for (size_t i = 0; i < function.size(); ++i){
        char c = function[i];

        // Substitui 'e' isolado
        if (c == 'e') {
            bool prevIsLetter = (i > 0 && isalpha((unsigned char)function[i-1]));
            bool nextIsLetter = (i + 1 < function.size() && isalpha((unsigned char)function[i+1]));

            if (!prevIsLetter && !nextIsLetter) {
                result.append(eulerText);
                continue;
            }
        }

        // Substitui variável
        if (c == variable) {
            bool prevIsLetter = (i > 0 && isalpha((unsigned char)function[i-1]));
            bool nextIsLetter = (i + 1 < function.size() && isalpha((unsigned char)function[i+1]));
            if (prevIsLetter || nextIsLetter) {
                result.push_back(c);
            } else {
                result.append(valueStr);
            }
            continue;
        }

        result.push_back(c);
    }

    return result;
}

// --- Parse seguro com tratamento de número com sinal unário ---
double FunctionParser::parse(const string& funcWithVar, char variable, double value){
    string func = variableToValue(funcWithVar, variable, value);

    if (any_of(func.begin(), func.end(), [](char ch){ return std::isalpha((unsigned char)ch); })) {
        cerr << "Error: Variable substitution failed, variable or characters still present in function." << endl;
        return NAN;
    }

    stack<double> output;
    stack<char> operands;

    bool expectUnary = true;

    for (size_t i = 0; i < func.length(); ++i){
        char c = func[i];

        if (c == ' ') continue;

        // --- Número e unário tipo -2 ou +3 ---
        if (isdigit((unsigned char)c) ||
            ((c == '+' || c == '-') && expectUnary && i + 1 < func.length() &&
             (isdigit((unsigned char)func[i+1]) || func[i+1] == '.'))) {

            string num_str;
            if ((c == '+' || c == '-') && expectUnary) {
                num_str.push_back(c);
                ++i;
            }

            while (i < func.length() && (isdigit((unsigned char)func[i]) || func[i] == '.')) {
                num_str.push_back(func[i]);
                ++i;
            }
            --i;

            try {
                output.push(stod(num_str));
            } catch (...) {
                cerr << "Conversion to double failed for token: " << num_str << endl;
                return NAN;
            }

            expectUnary = false;
            continue;
        }

        // --- Abre parênteses ---
        if (c == '(') {
            operands.push(c);
            expectUnary = true;
            continue;
        }

        // --- Fecha parênteses ---
        if (c == ')') {
            while (!operands.empty() && operands.top() != '(') {
                if (output.size() < 2) {
                    cerr << "Insufficient operands" << endl;
                    return NAN;
                }
                double b = output.top(); output.pop();
                double a = output.top(); output.pop();
                char op = operands.top(); operands.pop();

                output.push(evaluateOp(a, op, b));
            }
            if (operands.empty()) {
                cerr << "Unbalanced parenthesis" << endl;
                return NAN;
            }
            operands.pop();
            expectUnary = false;
            continue;
        }

        // --- Operadores ---
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {

            // ✅ PATCH: unário antes de '('
            if (expectUnary && (c == '+' || c == '-')) {
                if (i + 1 < func.length() && func[i+1] == '(') {
                    output.push(0);
                    operands.push(c);
                    expectUnary = true;
                    continue;
                }
                cerr << "Syntax error: unexpected operator " << c << endl;
                return NAN;
            }

            while (!operands.empty() && operands.top() != '(' &&
                   precedence(operands.top()) >= precedence(c)) {

                if (output.size() < 2) {
                    cerr << "Insufficient operands" << endl;
                    return NAN;
                }

                double b = output.top(); output.pop();
                double a = output.top(); output.pop();
                char op = operands.top(); operands.pop();

                output.push(evaluateOp(a, op, b));
            }

            operands.push(c);
            expectUnary = true;
            continue;
        }

        cerr << "Invalid character in expression: '" << c << "'" << endl;
        return NAN;
    }

    while (!operands.empty()) {
        if (operands.top() == '(') {
            cerr << "Syntax Error: mismatched parenthesis" << endl;
            return NAN;
        }

        if (output.size() < 2) {
            cerr << "Insufficient operands when finalizing" << endl;
            return NAN;
        }

        double b = output.top(); output.pop();
        double a = output.top(); output.pop();
        char op = operands.top(); operands.pop();

        output.push(evaluateOp(a, op, b));
    }

    if (output.empty()) {
        cerr << "No result on output stack" << endl;
        return NAN;
    }

    return output.top();
}

double FunctionParser::evaluateOp(double a, char op, double b){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0){
                cerr << "Division by zero!" << endl;
                return NAN;
            }
            return a / b;
        case '^': return pow(a, b);
    }
    cerr << "Invalid operator '" << op << "'" << endl;
    return NAN;
}

int FunctionParser::precedence(char op){
    switch(op){
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return -1;
}

double FunctionParser::parse(const string& funcWithoutVar) {
    return parse(funcWithoutVar, ' ', 0);
}

double FunctionParser::parse(const string& funcWithoutVar, double value) {
    return parse(funcWithoutVar, 'x', value);
}
