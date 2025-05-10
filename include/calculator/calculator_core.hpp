#ifndef CALCULATOR_CORE_H
#define CALCULATOR_CORE_H

#include <stdexcept>
#include <string>
#include <vector>

/**
 * @class CalculatorCore
 * @brief Core calculator engine supporting arithmetic operations with proper precedence and parentheses
 */
class CalculatorCore {
public:
    CalculatorCore();
    ~CalculatorCore();

    // Delete copy/move operations for singleton-like behavior
    CalculatorCore(const CalculatorCore&) = delete;
    CalculatorCore(CalculatorCore&&) = delete;
    CalculatorCore& operator=(const CalculatorCore&) = delete;
    CalculatorCore& operator=(CalculatorCore&&) = delete;

    /**
     * @brief Perform a calculation based on the input string
     * @param expression The mathematical expression to evaluate
     * @return The result of the calculation
     * @throws std::runtime_error if the expression is invalid
     */
    double calculate(const std::string& expression);

    // Memory operations
    // void storeInMemory(double value);
    // double recallMemory() const;
    // void clearMemory();

private:
    // double memory = 0.0;  // For future memory feature

    struct Token {
        enum Type { Number, Operator, Parenthesis };
        Type type;
        std::string value;
    };

    /**
     * @brief Checks if a character is an operator
     * @return true if the character is an operator, false otherwise
     */
    static bool isOperator(char c);

    /**
     * @brief Converts expression string into tokens
     * @throws std::runtime_error for invalid characters
     */
    std::vector<Token> tokenize(const std::string& expression) const;

    /**
     * @brief Converts infix tokens to postfix notation (RPN)
     * @throws std::runtime_error for mismatched parentheses
     */
    std::vector<Token> shuntingYard(const std::vector<Token>& tokens) const;

    /**
     * @brief Evaluates postfix (RPN) expression
     * @throws std::runtime_error for invalid operations
     */
    double evaluatePostfix(const std::vector<Token>& rpn) const;

    /**
     * @brief Gets operator precedence
     * @return int Precedence level (higher = earlier evaluation)
     */
    int getPrecedence(char op) const;

    /**
     * @brief Applies a binary operation
     * @throws std::runtime_error for division by zero or unknown operators
     */
    double applyOperation(char op, double a, double b) const;
};

#endif // CALCULATOR_CORE_H
