#ifndef CALCULATOR_CORE_H
#define CALCULATOR_CORE_H

/**
 * @class CalculatorCore
 * @brief Core calculator functionality with basic and advanced math operations
 */
class CalculatorCore {
  public:
    CalculatorCore();
    ~CalculatorCore();

    // Basic arithmetic operations
    /**
     * @brief Add two numbers
     * @param a First operand
     * @param b Second operand
     * @return Sum of a and b
     */
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);

    // Memory operations
    // void storeInMemory(double value);
    // double recallMemory() const;
    // void clearMemory();

  private:
    double memory;
};

#endif // CALCULATOR_CORE_H
