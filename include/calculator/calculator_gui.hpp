#ifndef CALCULATOR_GUI_H
#define CALCULATOR_GUI_H

#include "calculator/calculator_core.hpp"

#include <memory>
#include <string>

struct GLFWwindow;

/**
 * @class CalculatorGUI
 * @brief GUI wrapper for the Calculator class using ImGui
 */
class CalculatorGUI {
  public:
    CalculatorGUI();
    ~CalculatorGUI();

    // Delete copy/move operations
    CalculatorGUI(const CalculatorGUI &) = delete;
    CalculatorGUI(CalculatorGUI &&) = delete;
    CalculatorGUI &operator=(const CalculatorGUI &) = delete;
    CalculatorGUI &operator=(CalculatorGUI &&) = delete;

    /**
     * @brief Initialize the GUI
     * @return true if successful, false otherwise
     */
    [[nodiscard]] bool initialize();

    /**
     * @brief Run the main application loop
     */
    void run();

  private:
    GLFWwindow *m_window = nullptr;
    std::unique_ptr<CalculatorCore> m_calculator_core;
    double m_result = 0.0;
    std::string m_displayBuffer = "0";

    /**
     * @brief Render the GUI
     */
    void render();

    /**
     * @brief Process the button click
     */
    // void processButtonClick(const std::string& label);
};

#endif // CALCULATOR_GUI_H
