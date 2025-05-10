add_library(calculator_core calculator_core.cpp)

target_include_directories(calculator_core
    PRIVATE
    ../../include
)

if(MSVC)
    target_compile_options(calculator_core PRIVATE /W4 /WX)
else()
    target_compile_options(calculator_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
