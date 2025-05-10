#include "calculator/calculator_core.hpp"
#include <stdexcept>

CalculatorCore::CalculatorCore() : memory(0.0) {}

CalculatorCore::~CalculatorCore() {}

double CalculatorCore::add(double a, double b) { return a + b; }

double CalculatorCore::subtract(double a, double b) { return a - b; }

double CalculatorCore::multiply(double a, double b) { return a * b; }

double CalculatorCore::divide(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Error: Division by zero");
    }
    return a / b;
}
