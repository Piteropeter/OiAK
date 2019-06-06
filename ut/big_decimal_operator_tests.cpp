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
    EXPECT_EQ(x.to_exponential_notation(), "123000000123 * 2 ^ -18");
}

TEST(big_decimal_operator_tests, different_exponents_positive_and_negative_sum) {
    auto x = BigDecimal("123000");
    auto y = BigDecimal("-0.000123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "122fff.fffedd");
    EXPECT_EQ(x.to_exponential_notation(), "122ffffffedd * 2 ^ -18");
}

TEST(big_decimal_operator_tests, different_exponents_negative_and_positive_sum) {
    auto x = BigDecimal("-123000");
    auto y = BigDecimal("0.000123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "-122fff.fffedd");
    EXPECT_EQ(x.to_exponential_notation(), "-122ffffffedd * 2 ^ -18");
}

TEST(big_decimal_operator_tests, same_exponents_positive_and_negative_sum) {
    auto x = BigDecimal("123000");
    auto y = BigDecimal("-123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "122edd");
    EXPECT_EQ(x.to_exponential_notation(), "122edd * 2 ^ 0");
}

TEST(big_decimal_operator_tests, same_exponents_negative_and_positive_sum) {
    auto x = BigDecimal("-123000");
    auto y = BigDecimal("100");
    x = x + y;
    EXPECT_EQ(x.to_string(), "-122f00");
    EXPECT_EQ(x.to_exponential_notation(), "-122f * 2 ^ 8");
}

TEST(big_decimal_operator_tests, same_exponents_negative_and_positive_sum_to_zero) {
    auto x = BigDecimal("-123000");
    auto y = BigDecimal("123000");
    x = x + y;
    EXPECT_EQ(x.to_string(), "0");
    EXPECT_EQ(x.to_exponential_notation(), "0 * 2 ^ 0");
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


TEST(big_decimal_operator_tests, div_test_round_even_a) {
    auto x = BigDecimal("ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    auto y = BigDecimal("11111111111111111111111111111");
    x = x.divide(y,48, Round::symetric_even);
    EXPECT_EQ(x.to_string(), "f00000000000000000000000000000.0effffffffffffffffff");
}

TEST(big_decimal_operator_tests, div_test_round_even) {
    auto x = BigDecimal("5c4c");
    auto y = BigDecimal("cf0");
    x = x.divide(y, 5, Round::symetric_even);
    EXPECT_EQ(x.to_string(), "7.2252");
}

TEST(big_decimal_operator_tests, div_test_round_even_2) {
    auto x = BigDecimal("5c4c");
    auto y = BigDecimal("cf00");
    x = x.divide(y, 5, Round::symetric_even);
    EXPECT_EQ(x.to_string(), "0.72252");
}
TEST(big_decimal_operator_tests, div_test_round_even_3) {
    auto x = BigDecimal("5c4c");
    auto y = BigDecimal("cf000");
    x = x.divide(y, 5, Round::symetric_even);
    EXPECT_EQ(x.to_string(), "0.072252");
}

TEST(big_decimal_operator_tests, basic_dividing) {
    auto x = BigDecimal("16.8");
    auto y = BigDecimal("2d");
    x = x / y;
    EXPECT_EQ(x.to_string(), "0.8");
}

TEST(big_decimal_operator_tests, different_exponents_dividing) {
    auto x = BigDecimal("246000");
    auto y = BigDecimal("0.123");
    x = x / y;
    EXPECT_EQ(x.to_string(), "2000000");
}

TEST(big_decimal_operator_tests, div_test_2) {
    auto x = BigDecimal("5c4c00");                              
    auto y = BigDecimal("3"); 
	x = x / y;
	EXPECT_EQ(x.to_string(), "1ec400");
}

TEST(big_decimal_operator_tests, div_test_3) {
    auto x = BigDecimal("5c4c");
    auto y = BigDecimal("cf0");
    x = x / y;
    EXPECT_EQ(x.to_string(), "7.22519f89467e2519f89467e2519f89467e2519f89467e2519f89467e2519f89");
}

TEST(big_decimal_operator_tests, div_test_4) {
    auto x = BigDecimal("5c4c");
    auto y = BigDecimal("cf0");
    x = x.divide(y,10,Round::symetric_even);
    EXPECT_EQ(x.to_string(), "7.22519f894");
}

TEST(big_decimal_operator_tests, div_test_5) {
    auto x = BigDecimal("5c4c0");
    auto y = BigDecimal("cf0");
    x = x.divide(y, 10, Round::symetric_even);
    EXPECT_EQ(x.to_string(), "72.2519f894");
}


TEST(big_decimal_operator_tests, div_test_round_cut) {
    auto x = BigDecimal("5c4c");
    auto y = BigDecimal("cf00");
    x = x.divide(y, 5, Round::cut);
    EXPECT_EQ(x.to_string(), "0.72251");
}

TEST(big_decimal_operator_tests, div_test_round_floor) {
    auto x = BigDecimal("5c4c");
    auto y = BigDecimal("cf00");
    x = x.divide(y, 5, Round::floor);
    EXPECT_EQ(x.to_string(), "0.72251");
}

TEST(big_decimal_operator_tests, div_test_round_floor_2) {
    auto x = BigDecimal("-5c4c");
    auto y = BigDecimal("cf00");
    x = x.divide(y, 5, Round::floor);
    EXPECT_EQ(x.to_string(), "-0.72252");
}

TEST(big_decimal_operator_tests, div_test_round_ceil) {
    auto x = BigDecimal("5c4c");
    auto y = BigDecimal("cf00");
    x = x.divide(y, 5, Round::ceil);
    EXPECT_EQ(x.to_string(), "0.72252");
}

TEST(big_decimal_operator_tests, div_test_round_ceil_2) {
    auto x = BigDecimal("-5c4c");
    auto y = BigDecimal("cf00");
    x = x.divide(y, 5, Round::ceil);
    EXPECT_EQ(x.to_string(), "-0.72251");
    EXPECT_EQ(x.to_scientific_notation(), "-72251E-5");
}

/// OTHER OPERATORS

TEST(big_decimal_operator_tests, assignment_operator) {
    auto x = BigDecimal("129873.2134");
    auto y = BigDecimal("321.654");
    x = y;
    EXPECT_EQ(x.to_string(), "321.654");
}

} // namespace ut
