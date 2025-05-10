#include "calculator/calculator_gui.hpp"

#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "glad.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

namespace {
void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << '\n';
}
} // namespace

CalculatorGUI::CalculatorGUI() : m_calculator_core(std::make_unique<CalculatorCore>()) {}

CalculatorGUI::~CalculatorGUI() {
    if (ImGui::GetCurrentContext()) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
}

bool CalculatorGUI::initialize() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    // Configure OpenGL context
    constexpr std::string_view glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac

    // Create window with graphics context
    m_window = glfwCreateWindow(400, 400, "Calculator", nullptr, nullptr);
    if (m_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD (OpenGL loader)\n";
        return false;
    }

    // Verify OpenGL version
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    if (!glGetString(GL_VERSION)) {
        std::cerr << "OpenGL not properly initialized!\n";
        return false;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(m_window, true)) {
        std::cerr << "Failed to initialize ImGui GLFW backend\n";
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init(glsl_version.data())) {
        std::cerr << "Failed to initialize ImGui OpenGL3 backend\n";
        return false;
    }

    return true;
}

void CalculatorGUI::run() {
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render the GUI
        render();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
    }
}

void CalculatorGUI::render() {
    // Get window size
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);

    // Set next window to cover entire viewport
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    // Add flags to make it non-resizable, non-movable, etc.
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Calculator", nullptr, flags);

    // Display buffer
    ImGui::InputText("Display", &m_displayBuffer, ImGuiInputTextFlags_ReadOnly);

    // Button layout
    const std::array<std::array<std::string, 5>, 4> buttons = {
        {{"7", "8", "9", "/", "^"}, {"4", "5", "6", "*", "("}, {"1", "2", "3", "-", ")"}, {"0", ".", "=", "+", "C"}}};

    float available_width = ImGui::GetContentRegionAvail().x;
    float spacing = ImGui::GetStyle().ItemSpacing.x;
    int columns = buttons[0].size();
    float button_width = (available_width - (columns - 1) * spacing) / columns;
    float button_height = 50.0f;

    for (const auto& row : buttons) {
        ImGui::BeginGroup();
        for (size_t i = 0; i < row.size(); i++) {
            const auto& label = row[i];
            if (!label.empty()) {
                if (ImGui::Button(label.c_str(), ImVec2(button_width, button_height))) {
                    processButtonClick(label);
                }
                if (i < row.size() - 1) {
                    ImGui::SameLine();
                }
            }
        }
        ImGui::EndGroup();
    }

    ImGui::End();
}

void CalculatorGUI::processButtonClick(const std::string& label) {
    if (label == "=") {
        try {
            m_result = m_calculator_core->calculate(m_displayBuffer);

            // Format the output
            std::ostringstream oss;
            double intpart;
            if (std::modf(m_result, &intpart) == 0.0) {
                // Whole number
                oss << std::setprecision(0) << std::fixed << m_result;
            } else {
                // Decimal number - show up to 10 significant digits
                oss << std::setprecision(10) << m_result;
                auto str = oss.str();
                // Trim trailing zeros
                str.erase(str.find_last_not_of('0') + 1, std::string::npos);
                if (str.back() == '.')
                    str.pop_back();
                m_displayBuffer = str;
                return;
            }
            m_displayBuffer = oss.str();
        } catch (const std::exception& e) {
            m_displayBuffer = "Error";
        }
    } else if (label == "C") {
        m_displayBuffer.clear();
    } else {
        if (m_displayBuffer == "0") {
            m_displayBuffer.clear();
        }
        m_displayBuffer += label;
    }
}
