#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <algorithm> // for std::any_of
#include "functionParser.h"

using namespace std;

/*
 * Class to parse mathematical functions given as strings
 * Supports +, -, *, /, ^ operators and respects operator precedence
 * Example: "3^2 + 9*2 + 2 - 9/2"
*/


string FunctionParser::variableToValue(string function, char variable, double value){
    // Replace 'x' or other variable with its value in the function string
    string valueStr = to_string(value); 

    for (size_t i = 0; i < function.size(); i++) {
        if (function[i] == variable) {
            function.replace(i, 1, valueStr); 
            i += valueStr.size() - 1;
        }
    }
    return function;
}

// Aux function: Evaluete operation between to doubles
double FunctionParser::evaluateOp(double a, char op, double b){
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
int FunctionParser::precedence(char op){
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    if(op == '^') return 3;
    return -1;
}

/* Polimorfism for parse, to handle functions without specifying the variable */
double FunctionParser::parse(const string& funcWithoutVar, double value){
    // Try to detect variable in the function string
    for(char c : funcWithoutVar){
        if(isalpha(static_cast<unsigned char>(c))){
            // cout << "Variable detected: " << c << endl;
            return parse(funcWithoutVar, c, value);
        }
    }
    // No variable detected, parse directly
    return parse(funcWithoutVar, 'x', value);

}

// Polimorfism for parse, to handle functions without variable and value
double FunctionParser::parse(const string& funcWithoutVar){
    return parse(funcWithoutVar, 0);
}

// Main function to parse
double FunctionParser::parse(const string& funcWithVar, char variable, double value){
    // cout << "Parsing function: " << funcWithVar << " with variable " << variable << " = " << value << endl;
    string func = variableToValue(funcWithVar, variable, value);

    if(any_of(func.begin(), func.end(), ::isalpha)){
        cerr << "Error: Variable substitution failed, variable or characters still present in function." << endl;
        return NAN;
    }

    stack<double> output;
    stack<char> operands;

    for(size_t i = 0; i < func.length(); i++){
        if(func[i] == ' ') continue;

        string num_str;
        while((i < func.length()) && (isdigit(func[i]) || func[i] == '.')){
            num_str += func[i];
            i++;
        }

        if(!num_str.empty()){
            output.push(stod(num_str));
            i--;
        }

        else if(func[i] == '('){
            operands.push(func[i]);
        }    

        else if(func[i] == ')'){
            while(!operands.empty() && operands.top() != '('){

                if(output.size() < 2){
                    cerr << "Insufficient operands" << endl;
                    return NAN;
                }

                double val2 = output.top(); output.pop();
                double val1 = output.top(); output.pop();

                char op = operands.top(); operands.pop();

                double result = evaluateOp(val1, op, val2);
                if(isnan(result)) return NAN;
                output.push(result);
            }

            if(!operands.empty() && operands.top() == '('){
                operands.pop();
            }else{
                cerr << "unbalanced parenteshis" << endl;
                return NAN;
            }
        }
        else{
            char op = func[i];

           while(!operands.empty() && operands.top() != '(' && precedence(operands.top()) >= precedence(op)){
                char op = operands.top(); operands.pop();
                double val2 = output.top(); output.pop();
                double val1 = output.top(); output.pop();

                double result = evaluateOp(val1, op, val2);
                // cout << "Avaliando ops: " << val1 << " " << op << " " << val2 << " result " << result << endl;
                output.push(result);
            }
            operands.push(op);
        }
    }

    while(!operands.empty()){
        if (operands.top() == '('){
            cerr << " Sintax Error" << endl; 
            return NAN;
        }
        
        char op = operands.top(); operands.pop();
        double val2 = output.top(); output.pop();
        double val1 = output.top(); output.pop();
        
        double result = evaluateOp(val1, op, val2);
        // cout << "Avaliando ops: " << val1 << " " << op << " " << val2 << " result " << result << endl;
        output.push(result);
    }

    return output.top();
}


void FunctionParser::test(){

    FunctionParser fParser;

    // First test
    cout << "\nFirst Test:" << endl;
    string func1 = "y^2 + y + 1";
    char variable1 = 'y';
    double value1 = 10;
    double result1 = fParser.parse(func1, variable1, value1);
    cout << "The final result is: " << result1 << endl;

    // Second test
    cout << "\nSecond Test:" << endl;
    string func2 = "3^2 + 9*2 + 2 - 9/2";
    double value2 = 0; // No variable in this function
    double result2 = fParser.parse(func2, value2);
    cout << "The final result is: " << result2 << endl;

    // Third test
    cout << "\nThird Test:" << endl;
    string func3 = "2^3.2 + 4 - 5";
    double result3 = fParser.parse(func3);
    cout << "The final result is: " << result3 << endl;

    // Fourth test (*proposital error to test variable detection*)
    cout << "\nFourth Test:" << endl;
    string func4 = "fdx^3 + 2*x^2 + 3*x + 4";
    double value4 = 2;
    double result4 = fParser.parse(func4, value4);
    cout << "The final result is: " << result4 << endl;
   
}