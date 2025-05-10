#include "calculator/calculator_core.hpp"
#include <gtest/gtest.h>

class CalculatorTest : public ::testing::Test {
  protected:
    CalculatorCore calc;
};

TEST_F(CalculatorTest, Add) {
    EXPECT_EQ(calc.add(1, 2), 3);
    EXPECT_EQ(calc.add(-1, 1), 0);
    EXPECT_EQ(calc.add(0, 0), 0);
    EXPECT_EQ(calc.add(-1, -1), -2);
    EXPECT_EQ(calc.add(1.5, 2.5), 4.0);
    EXPECT_EQ(calc.add(1.5, -2.5), -1.0);
    EXPECT_EQ(calc.add(-1.5, 2.5), 1.0);
}

TEST_F(CalculatorTest, Subtract) {
    EXPECT_EQ(calc.subtract(5, 3), 2);
    EXPECT_EQ(calc.subtract(3, 5), -2);
    EXPECT_EQ(calc.subtract(0, 0), 0);
    EXPECT_EQ(calc.subtract(-1, -1), 0);
    EXPECT_EQ(calc.subtract(1.5, 0.5), 1.0);
    EXPECT_EQ(calc.subtract(1.5, -0.5), 2.0);
    EXPECT_EQ(calc.subtract(-1.5, -2.5), 1.0);
}

TEST_F(CalculatorTest, Multiply) {
    EXPECT_EQ(calc.multiply(2, 3), 6);
    EXPECT_EQ(calc.multiply(-2, 3), -6);
    EXPECT_EQ(calc.multiply(0, 5), 0);
    EXPECT_EQ(calc.multiply(-2, -3), 6);
    EXPECT_EQ(calc.multiply(1.5, 2.0), 3.0);
    EXPECT_EQ(calc.multiply(1.5, -2.0), -3.0);
    EXPECT_EQ(calc.multiply(-1.5, -2.0), 3.0);
}

TEST_F(CalculatorTest, Divide) {
    EXPECT_EQ(calc.divide(6, 3), 2);
    EXPECT_EQ(calc.divide(-6, 3), -2);
    EXPECT_EQ(calc.divide(0, 5), 0);
    EXPECT_EQ(calc.divide(-6, -3), 2);
    EXPECT_EQ(calc.divide(1.5, 0.5), 3.0);
    EXPECT_EQ(calc.divide(1.5, -0.5), -3.0);
    EXPECT_EQ(calc.divide(-1.5, -0.5), 3.0);
    EXPECT_THROW(calc.divide(1, 0), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
