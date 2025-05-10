cmake_minimum_required(VERSION 3.10)
project(calculator VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Option for building tests
option(BUILD_TESTS "Build test applications" OFF)

# GLFW
add_subdirectory(external/glfw)

# GLAD
add_library(glad STATIC external/glad/glad.c)
target_include_directories(glad PUBLIC external/glad)

# ImGui source files
set(IMGUI_SOURCES
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
    external/imgui/misc/cpp/imgui_stdlib.cpp
)

# Create imgui library
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui
    PUBLIC
    external/imgui
    external/imgui/backends
    external/imgui/misc/cpp
)

# OpenGL
find_package(OpenGL REQUIRED)

target_link_libraries(imgui
    PUBLIC
    glfw
    OpenGL::GL
    glad
)

# Add subdirectories for each component
add_subdirectory(src/core)
add_subdirectory(src/gui)

# Main application executable
add_executable(calculator src/main.cpp)
target_include_directories(calculator PRIVATE include)
target_link_libraries(calculator
    PRIVATE
    calculator_core
    calculator_gui
)

# Add compiler warnings and flags
if(MSVC)
    target_compile_options(calculator PRIVATE /W4 /WX)
else()
    target_compile_options(calculator PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
