#include "functionParser.h"

// substitui variável e 'e'
string FunctionParser::variableToValue(string function, char variable, double value){
    string result;
    result.reserve(function.size() + 32);

    // formata value sem zeros extras e com sinal
    ostringstream oss;
    oss << setprecision(12) << value;
    string valueStr = oss.str();
    if (value < 0 && valueStr.front() != '(') valueStr = "(" + valueStr + ")";

    // 'e' vira diretamente a constante 
    const string eulerText = "2.718281828459045";

    for (size_t i = 0; i < function.size(); ++i){
        char c = function[i];

        // substitui 'e' isolado
        if (c == 'e') {
            bool prevIsLetter = (i > 0 && isalpha((unsigned char)function[i-1]));
            bool nextIsLetter = (i + 1 < function.size() && isalpha((unsigned char)function[i+1]));

            if (!prevIsLetter && !nextIsLetter) {
                result.append(eulerText);
                continue;
            }
        }

        // substitui variável
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

// parse seguro com tratamento de número com sinal unário
double FunctionParser::parse(const string& funcWithVar, char variable, double value){
    string func = variableToValue(funcWithVar, variable, value);

    if (any_of(func.begin(), func.end(), [](char ch){ return isalpha((unsigned char)ch); })) {
        cout << func << endl;
        cerr << "Erro: Falha na substituição da variável, variável ou caracteres ainda presentes na função." << endl;
        return NAN;
    }

    stack<double> output;
    stack<char> operands;

    bool expectUnary = true;

    for (size_t i = 0; i < func.length(); ++i){
        char c = func[i];

        if (c == ' ') continue;

        // número e unário (tipo -2 ou +3)
        if (isdigit((unsigned char)c) ||
            ((c == '+' || c == '-') && expectUnary && i + 1 < func.length() &&
             (isdigit((unsigned char)func[i+1]) || func[i+1] == '.'))) {

            string num_str;
            if ((c == '+' || c == '-') && expectUnary) {
                num_str.push_back(c);
                ++i;
            }

            // coleta o número completo
            while (i < func.length() && (isdigit((unsigned char)func[i]) || func[i] == '.')) {
                num_str.push_back(func[i]);
                ++i;
            }
            --i;

            try {
                output.push(stod(num_str));
            } catch (...) {
                cerr << "Conversão para double falhou para o token: " << num_str << endl;
                return NAN;
            }

            expectUnary = false;
            continue;
        }

        // abre parênteses
        if (c == '(') {
            operands.push(c);
            expectUnary = true;
            continue;
        }

        // fecha parênteses
        if (c == ')') {
            while (!operands.empty() && operands.top() != '(') {
                if (output.size() < 2) {
                    cerr << "Operandos insuficientes" << endl;
                    return NAN;
                }
                double b = output.top(); output.pop();
                double a = output.top(); output.pop();
                char op = operands.top(); operands.pop();

                output.push(evaluateOp(a, op, b));
            }
            if (operands.empty()) {
                cerr << "Parênteses desequilibrados" << endl;
                return NAN;
            }
            operands.pop();
            expectUnary = false;
            continue;
        }

        // operadores
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {

            // unário antes de '('
            if (expectUnary && (c == '+' || c == '-')) {
                if (i + 1 < func.length() && func[i+1] == '(') {
                    output.push(0);
                    operands.push(c);
                    expectUnary = true;
                    continue;
                }
                cerr << "Erro de sintaxe: operador inesperado " << c << endl;
                return NAN;
            }

            while (!operands.empty() && operands.top() != '(' &&
                   precedence(operands.top()) >= precedence(c)) {

                if (output.size() < 2) {
                    cerr << "Operandos insuficientes" << endl;
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

        cerr << "Caractere inválido na expressão: '" << c << "'" << endl;
        return NAN;
    }

    while (!operands.empty()) {
        if (operands.top() == '(') {
            cerr << "Erro de sintaxe: parênteses incompatíveis" << endl;
            return NAN;
        }

        if (output.size() < 2) {
            cerr << "Operandos insuficientes ao finalizar" << endl;
            return NAN;
        }

        double b = output.top(); output.pop();
        double a = output.top(); output.pop();
        char op = operands.top(); operands.pop();

        output.push(evaluateOp(a, op, b));
    }

    if (output.empty()) {
        cerr << "Nenhum resultado na pilha de saída" << endl;
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
                cerr << "Divisão por zero!" << endl;
                return NAN;
            }
            return a / b;
        case '^': return pow(a, b);
    }
    cerr << "Operador inválido '" << op << "'" << endl;
    return NAN;
}

// precedência de operadores
int FunctionParser::precedence(char op){
    switch(op){
        case '+': case '-': return  1;
        case '*': case '/': return  2;
        case '^':           return  3;
        default:            return -1;
    }
}

double FunctionParser::parse(const string& funcWithoutVar) {
    return parse(funcWithoutVar, ' ', 0);
}

double FunctionParser::parse(const string& funcWithoutVar, double value){
    // tenta detectar a variável na string da função
    for(char c : funcWithoutVar){
        if(isalpha(static_cast<unsigned char>(c)) && c != 'e'){
            // cout << "variavel detectada: " << c << endl;
            return parse(funcWithoutVar, c, value);
        }
    }
    // nenhuma variável, parse direto
    return parse(funcWithoutVar, 'x', value);
}

