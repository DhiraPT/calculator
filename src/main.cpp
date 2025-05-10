#include "calculator/calculator_gui.hpp"

#include <iostream>

int main() {
    try {
        CalculatorGUI gui;
        if (!gui.initialize()) {
            std::cerr << "Failed to initialize GUI\n";
            return 1;
        }

        // Run the main loop
        gui.run();

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
