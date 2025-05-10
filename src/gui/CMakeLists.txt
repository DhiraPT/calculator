add_library(calculator_gui calculator_gui.cpp)

target_include_directories(calculator_gui
    PRIVATE
    ../../include
    ../../external/imgui
    ../../external/imgui/backends
    ../../external/imgui/misc/cpp
    ../../external/glad
)

target_link_libraries(calculator_gui
    PRIVATE
    calculator_core
    imgui
    glfw
    OpenGL::GL
    glad
    ${CMAKE_DL_LIBS}
)

# Add platform-specific compile definitions for GLFW
target_compile_definitions(calculator_gui
    PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLAD
)

if(MSVC)
    target_compile_options(calculator_gui PRIVATE /W4 /WX)
else()
    target_compile_options(calculator_gui PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
