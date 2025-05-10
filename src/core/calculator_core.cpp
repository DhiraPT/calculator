#include "calculator/calculator_core.hpp"

#include <cctype>
#include <cmath>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

CalculatorCore::CalculatorCore() {}

CalculatorCore::~CalculatorCore() {}

double CalculatorCore::calculate(const std::string& expression) {
    auto tokens = tokenize(expression);
    auto rpn = shuntingYard(tokens);
    return evaluatePostfix(rpn);
}

bool CalculatorCore::isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }

std::vector<CalculatorCore::Token> CalculatorCore::tokenize(const std::string& expression) const {
    std::vector<Token> tokens;
    for (size_t i = 0; i < expression.size();) {
        if (isspace(expression[i])) {
            i++;
            continue;
        }

        if (isdigit(expression[i]) || expression[i] == '.') {
            std::string numStr;
            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                numStr += expression[i++];
            }
            tokens.push_back({Token::Number, numStr});
        } else if (expression[i] == '(' || expression[i] == ')') {
            tokens.push_back({Token::Parenthesis, std::string(1, expression[i++])});
        } else if (isOperator(expression[i])) {
            tokens.push_back({Token::Operator, std::string(1, expression[i++])});
        } else {
            throw std::runtime_error("Invalid character in expression: " + std::string(1, expression[i]));
        }
    }
    return tokens;
}

std::vector<CalculatorCore::Token> CalculatorCore::shuntingYard(const std::vector<Token>& tokens) const {
    std::vector<Token> output;
    std::stack<Token> ops;

    for (const auto& token : tokens) {
        switch (token.type) {
        case Token::Number:
            output.push_back(token);
            break;

        case Token::Parenthesis:
            if (token.value == "(") {
                ops.push(token);
            } else {
                while (!ops.empty() && ops.top().value != "(") {
                    output.push_back(ops.top());
                    ops.pop();
                }
                if (ops.empty()) {
                    throw std::runtime_error("Mismatched parentheses");
                }
                ops.pop(); // Remove '('
            }
            break;

        case Token::Operator:
            while (!ops.empty() && ops.top().type == Token::Operator &&
                   getPrecedence(ops.top().value[0]) >= getPrecedence(token.value[0])) {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
            break;
        }
    }

    while (!ops.empty()) {
        if (ops.top().value == "(") {
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}

double CalculatorCore::evaluatePostfix(const std::vector<Token>& rpn) const {
    std::stack<double> values;

    for (const auto& token : rpn) {
        if (token.type == Token::Number) {
            values.push(std::stod(token.value));
        } else {
            if (values.size() < 2) {
                throw std::runtime_error("Invalid expression: not enough operands");
            }
            double b = values.top();
            values.pop();
            double a = values.top();
            values.pop();
            values.push(applyOperation(token.value[0], a, b));
        }
    }

    if (values.size() != 1) {
        throw std::runtime_error("Invalid expression: too many operands");
    }

    return values.top();
}

int CalculatorCore::getPrecedence(char op) const {
    switch (op) {
    case '^':
        return 4;
    case '*':
    case '/':
        return 3;
    case '+':
    case '-':
        return 2;
    default:
        return 0;
    }
}

double CalculatorCore::applyOperation(char op, double a, double b) const {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
            throw std::runtime_error("Division by zero");
        return a / b;
    case '^':
        return std::pow(a, b);
    default:
        throw std::runtime_error("Unknown operator: " + std::string(1, op));
    }
}
