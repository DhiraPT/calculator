find_package(GTest REQUIRED)

# Test executable
add_executable(test_calculator test_calculator.cpp)
target_link_libraries(test_calculator
    PRIVATE
    calculator_core
    GTest::GTest
    GTest::Main
)

target_include_directories(test_calculator
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Register test
add_test(NAME CalculatorTests COMMAND test_calculator)
