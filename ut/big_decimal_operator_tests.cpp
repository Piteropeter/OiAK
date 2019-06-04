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
    EXPECT_EQ(x.to_science_notation(), "123000000123 * 2 ^ -24");
}

TEST(big_decimal_operator_tests, different_exponents_positive_and_negative_sum) {
    auto x = BigDecimal("123000");
    auto y = BigDecimal("-0.000123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "122fff.fffedd"); // 122fff fffedd * 16^(-6) = 122ff fffedd * 2^4^(-6) = ... * 2^(-24) ??
    EXPECT_EQ(x.to_science_notation(), "122ffffffedd * 2 ^ -24");
}

TEST(big_decimal_operator_tests, different_exponents_negative_and_positive_sum) {
    auto x = BigDecimal("-123000");
    auto y = BigDecimal("0.000123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "-122fff.fffedd");
    EXPECT_EQ(x.to_science_notation(), "-122ffffffedd * 2 ^ -24");
}

TEST(big_decimal_operator_tests, same_exponents_positive_and_negative_sum) {
    auto x = BigDecimal("123000");
    auto y = BigDecimal("-123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "122edd");
    EXPECT_EQ(x.to_science_notation(), "122edd * 2 ^ 0");
}

TEST(big_decimal_operator_tests, same_exponents_negative_and_positive_sum) {
    auto x = BigDecimal("-123000");
    auto y = BigDecimal("100");
    x = x + y;
    EXPECT_EQ(x.to_string(), "-122f00");
    EXPECT_EQ(x.to_science_notation(), "-122f * 2 ^ 8");
}

TEST(big_decimal_operator_tests, same_exponents_negative_and_positive_sum_to_zero) {
    auto x = BigDecimal("-123000");
    auto y = BigDecimal("123000");
    x = x + y;
    EXPECT_EQ(x.to_string(), "0");
    EXPECT_EQ(x.to_science_notation(), "0 * 2 ^ 0");
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

TEST(big_decimal_operator_tests, rounding_test) {
    auto x = BigDecimal("4.25");
    auto y = BigDecimal("3.8253825382538253825382538253825");
    x = x / y;
    EXPECT_EQ(x.to_string(), "1.11");
}

/// OTHER OPERATORS

TEST(big_decimal_operator_tests, assignment_operator) {
    auto x = BigDecimal("129873.2134");
    auto y = BigDecimal("321.654");
    x = y;
    EXPECT_EQ(x.to_string(), "321.654");
}

} // namespace ut
