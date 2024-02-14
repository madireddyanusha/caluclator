#include <iostream>
#include <cmath>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// Function to evaluate the expression
double evaluateExpression(const string& expression) {
    stack<double> operands;
    stack<char> operators;

    for (size_t i = 0; i < expression.length(); ++i) {
        if (isspace(expression[i])) {
            continue;
        } else if (isdigit(expression[i])) {
            string operandStr;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                operandStr += expression[i];
                ++i;
            }
            --i;
            operands.push(stod(operandStr));
        } else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double operand2 = operands.top(); operands.pop();
                double operand1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                double result;
                switch (op) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        if (operand2 != 0)
                            result = operand1 / operand2;
                        else {
                            cerr << "Error! Division by zero!";
                            return NAN; // Not-a-Number
                        }
                        break;
                    case '^':
                        result = pow(operand1, operand2);
                        break;
                }
                operands.push(result);
            }
            operators.pop(); // Discard the opening parenthesis
        } else {
            while (!operators.empty() && operators.top() != '(' && ((expression[i] == '*' || expression[i] == '/') || 
                (expression[i] == '+' || expression[i] == '-') || 
                (expression[i] == '^'))) {
                double operand2 = operands.top(); operands.pop();
                double operand1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                double result;
                switch (op) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        if (operand2 != 0)
                            result = operand1 / operand2;
                        else {
                            cerr << "Error! Division by zero!";
                            return NAN; // Not-a-Number
                        }
                        break;
                    case '^':
                        result = pow(operand1, operand2);
                        break;
                }
                operands.push(result);
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.empty()) {
        double operand2 = operands.top(); operands.pop();
        double operand1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        double result;
        switch (op) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 != 0)
                    result = operand1 / operand2;
                else {
                    cerr << "Error! Division by zero!";
                    return NAN; // Not-a-Number
                }
                break;
            case '^':
                result = pow(operand1, operand2);
                break;
        }
        operands.push(result);
    }

    return operands.top();
}

int main() {
    string expression;
    cout << "Enter expression: ";
    getline(cin, expression);

    double result = evaluateExpression(expression);

    if (!isnan(result)) {
        cout << "Result: " << result << endl;
    }

    return 0;
}
