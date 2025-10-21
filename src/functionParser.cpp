#include <iostream>
#include <string>
#include <cmath>
#include <stack>

using namespace std;


class FunctionParser{
    public:

    
    
    // Aux function: Evaluete operation between to doubles
    double evaluateOp(double a, char op, double b){
        switch(op){
            case '+': return a+b;
            case '-': return a-b;
            case '*': return a*b;
            case '/': return (b!=0) ? a/b : (cerr << "Division by 0 impossible" << endl, NAN); 
            case '^': return pow(a, b);
        }
        return  (cerr << "Not a valid operation" << op << endl, NAN);
    }

    // Aux function: Return the op precedence number
    int precedence(char op){
        if(op == '+' || op == '-') return 1;
        if(op == '*' || op == '/') return 2;
        if(op == '^') return 3;
        return -1;
    }

    // Main function to parse
    double parse(const string& function, double value){
        cout << "Iniciando o parsing..." << endl;

        stack<double> output;
        stack<char> operands;

        for(int i = 0; i < function.length(); i++){
            if(function[i] == ' ') continue;

            string num_str;
            while((i < function.length()) && (isdigit(function[i]) || function[i] == '.')){
                num_str += function[i];
                i++;
            }
            if(!num_str.empty()){
                output.push(stod(num_str));
                i--;
            }
            else{
                char op = function[i];
                cout << "Op: " << op << endl;
                if(operands.empty() || (precedence(op) > precedence(operands.top()))){
                    operands.push(op);
                }
                else{
                    while(!operands.empty() && precedence(op) <= precedence(operands.top())){
                        char op = operands.top(); operands.pop();
                        double val2 = output.top(); output.pop();
                        double val1 = output.top(); output.pop();

                        double result = evaluateOp(val1, op, val2);
                        cout << "Avaliando ops: " << val1 << " " << op << " " << val2 << " result " << result << endl;
                        output.push(result);
                    }
                    operands.push(op);
                }
            }
        }
        // DEPURAÇÃO
        // while(!output.empty()){
        //     cout << output.top() << endl;
        //     output.pop();
        // }

        while(!operands.empty()){
            char op = operands.top(); operands.pop();
            double val2 = output.top(); output.pop();
            double val1 = output.top(); output.pop();
            
            double result = evaluateOp(val1, op, val2);
            cout << "Avaliando ops: " << val1 << " " << op << " " << val2 << " result " << result << endl;
            output.push(result);
        }

        return output.top();
    }
};

int main(){

    FunctionParser fParser;

    string funcao = "3^2 + 9*2 + 2 - 9/2";
    double resultado = fParser.parse(funcao, 4);
    cout << "O resultado é " << resultado << endl;

    // Depuraçao 
    // cout << "A funcao eh: " << funcao << endl; 
    // double resultado = fParser.parse(funcao, 4);
    // cout << "O resultado é " << resultado << endl;
    // fParser.evaluateOp(4, '/', 0);
    // cout << fParser.precedence('+') << endl;


    return 0;
}