#include <gtest/gtest.h>
#include "BigDecimal.h"

namespace ut {
using namespace oiak;

/// SUM

TEST(big_decimal_operator_tests, basic_sum) {
    auto x = BigDecimal("123.456");
    auto y = BigDecimal("123.456");
    x = x + y;
    EXPECT_EQ(x.to_string(), "246.8ac");
}

TEST(big_decimal_operator_tests, different_exponents_sum) {
    auto x = BigDecimal("123000");
    auto y = BigDecimal("0.000123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "123000.000123");
    EXPECT_EQ(x.to_science_notation(), "123000000123 * 2 ^ -18");
}

/// SUBTRACTION

TEST(big_decimal_operator_tests, basic_subtraction) {
    auto x = BigDecimal("0.1234");
    auto y = BigDecimal("0.0123");
    x = x - y;
    EXPECT_EQ(x.to_string(), "0.1111");
}

TEST(big_decimal_operator_tests, different_exponents_subtraction) {
    auto x = BigDecimal("123000");
    auto y = BigDecimal("0.000123");
    x = x - y;
    EXPECT_EQ(x.to_string(), "122fff.fffedd");
}

/// MULTIPLYING

TEST(big_decimal_operator_tests, basic_multiplying) {
    auto x = BigDecimal("16.8");
    auto y = BigDecimal("16.8");
    x = x * y;
    EXPECT_EQ(x.to_string(), "1fa.4");
}

TEST(big_decimal_operator_tests, different_exponents_multiplying) {
    auto x = BigDecimal("123000");
    auto y = BigDecimal("-0.123");
    x = x * y;
    EXPECT_EQ(x.to_string(), "-14ac9");
}

/// DIVIDING

TEST(big_decimal_operator_tests, basic_dividing) {
    auto x = BigDecimal("16.8");
    auto y = BigDecimal("16.8");
    x = x / y;
    EXPECT_EQ(x.to_string(), "1");
}

TEST(big_decimal_operator_tests, different_exponents_dividing) {
    auto x = BigDecimal("123000");
    auto y = BigDecimal("0.123");
    x = x / y;
    EXPECT_EQ(x.to_string(), "1000000");
}

/// OTHER OPERATORS

TEST(big_decimal_operator_tests, assignment_operator) {
    auto x = BigDecimal("129873.2134");
    auto y = BigDecimal("321.654");
    x = y;
    EXPECT_EQ(x.to_string(), "321.654");
}

} // namespace ut
