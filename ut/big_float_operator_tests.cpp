#include <gtest/gtest.h>
#include "BigFloat.h"

namespace ut {
using namespace oiak;

/// SUM

TEST(big_float_operator_tests, basic_sum) {
    auto x = BigFloat("123.456");
    auto y = BigFloat("123.456");
    x = x + y;
    EXPECT_EQ(x.to_string(), "246.8ac");
}

TEST(big_float_operator_tests, different_exponents_sum) {
    auto x = BigFloat("123000");
    auto y = BigFloat("0.000123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "123000.000123");
    EXPECT_EQ(x.to_exponential_notation(), "123000000123 * 2 ^ -18");
}

TEST(big_float_operator_tests, different_exponents_positive_and_negative_sum) {
    auto x = BigFloat("123000");
    auto y = BigFloat("-0.000123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "122fff.fffedd");
    EXPECT_EQ(x.to_exponential_notation(), "122ffffffedd * 2 ^ -18");
}

TEST(big_float_operator_tests, different_exponents_negative_and_positive_sum) {
    auto x = BigFloat("-123000");
    auto y = BigFloat("0.000123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "-122fff.fffedd");
    EXPECT_EQ(x.to_exponential_notation(), "-122ffffffedd * 2 ^ -18");
}

TEST(big_float_operator_tests, same_exponents_positive_and_negative_sum) {
    auto x = BigFloat("123000");
    auto y = BigFloat("-123");
    x = x + y;
    EXPECT_EQ(x.to_string(), "122edd");
    EXPECT_EQ(x.to_exponential_notation(), "122edd * 2 ^ 0");
}

TEST(big_float_operator_tests, same_exponents_negative_and_positive_sum) {
    auto x = BigFloat("-123000");
    auto y = BigFloat("100");
    x = x + y;
    EXPECT_EQ(x.to_string(), "-122f00");
    EXPECT_EQ(x.to_exponential_notation(), "-122f * 2 ^ 8");
}

TEST(big_float_operator_tests, same_exponents_negative_and_positive_sum_to_zero) {
    auto x = BigFloat("-123000");
    auto y = BigFloat("123000");
    x = x + y;
    EXPECT_EQ(x.to_string(), "0");
    EXPECT_EQ(x.to_exponential_notation(), "0 * 2 ^ 0");
}

/// SUBTRACTION

TEST(big_float_operator_tests, basic_subtraction) {
    auto x = BigFloat("0.1234");
    auto y = BigFloat("0.0123");
    x = x - y;
    EXPECT_EQ(x.to_string(), "0.1111");
}

TEST(big_float_operator_tests, different_exponents_subtraction) {
    auto x = BigFloat("123000");
    auto y = BigFloat("0.000123");
    x = x - y;
    EXPECT_EQ(x.to_string(), "122fff.fffedd");
}

TEST(big_float_operator_tests, same_exponents_subtraction) {
    auto x = BigFloat("0.000123");
    auto y = BigFloat("0.000122");
    x = x - y;
    EXPECT_EQ(x.to_string(), "0.000001");
}

/// MULTIPLYING

TEST(big_float_operator_tests, basic_multiplying) {
    auto x = BigFloat("16.8");
    auto y = BigFloat("16.8");
    x = x * y;
    EXPECT_EQ(x.to_string(), "1fa.4");
}

TEST(big_float_operator_tests, different_exponents_multiplying) {
    auto x = BigFloat("123000");
    auto y = BigFloat("-0.123");
    x = x * y;
    EXPECT_EQ(x.to_string(), "-14ac9");
}

TEST(big_float_operator_tests, same_exponents_multiplying) {
    auto x = BigFloat("-0.01");
    auto y = BigFloat("-0.01");
    x = x * y;
    EXPECT_EQ(x.to_string(), "0.0001");
}

/// DIVIDING

TEST(big_float_operator_tests, div_test_round_even1) {
    auto x = BigFloat("5c4c");
    auto y = BigFloat("cf0");
    x = x.divide(y, 5, BigFloat::Round::symetric_even);
    EXPECT_EQ(x.to_string(), "7.2252");
}

TEST(big_float_operator_tests, div_test_round_even2) {
    auto x = BigFloat("5c4c");
    auto y = BigFloat("cf00");
    x = x.divide(y, 5, BigFloat::Round::symetric_even);
    EXPECT_EQ(x.to_string(), "0.72252");
}
TEST(big_float_operator_tests, div_test_round_even3) {
    auto x = BigFloat("5c4c");
    auto y = BigFloat("cf000");
    x = x.divide(y, 5, BigFloat::Round::symetric_even);
    EXPECT_EQ(x.to_string(), "0.072252");
}

TEST(big_float_operator_tests, div_test_round_even4) {
    auto x = BigFloat("ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    auto y = BigFloat("11111111111111111111111111111");
    x = x.divide(y, 48, BigFloat::Round::symetric_even);
    EXPECT_EQ(x.to_string(), "f00000000000000000000000000000.0effffffffffffffffff");
}

TEST(big_float_operator_tests, basic_dividing) {
    auto x = BigFloat("16.8");
    auto y = BigFloat("2d");
    x = x / y;
    EXPECT_EQ(x.to_string(), "0.8");
}

TEST(big_float_operator_tests, different_exponents_dividing) {
    auto x = BigFloat("246000");
    auto y = BigFloat("0.123");
    x = x / y;
    EXPECT_EQ(x.to_string(), "2000000");
}

TEST(big_float_operator_tests, div_test_2) {
    auto x = BigFloat("5c4c00");
    auto y = BigFloat("3");
    x = x / y;
    EXPECT_EQ(x.to_string(), "1ec400");
}

TEST(big_float_operator_tests, div_test_3) {
    auto x = BigFloat("5c4c");
    auto y = BigFloat("cf0");
    x = x / y;
    EXPECT_EQ(x.to_string(), "7.22519f89467e2519f89467e2519f89467e2519f89467e2519f89467e2519f89");
}

TEST(big_float_operator_tests, div_test_4) {
    auto x = BigFloat("5c4c");
    auto y = BigFloat("cf0");
    x = x.divide(y, 10, BigFloat::Round::symetric_even);
    EXPECT_EQ(x.to_string(), "7.22519f894");
}

TEST(big_float_operator_tests, div_test_5) {
    auto x = BigFloat("5c4c0");
    auto y = BigFloat("cf0");
    x = x.divide(y, 10, BigFloat::Round::symetric_even);
    EXPECT_EQ(x.to_string(), "72.2519f894");
}

TEST(big_float_operator_tests, div_test_round_cut) {
    auto x = BigFloat("5c4c");
    auto y = BigFloat("cf00");
    x = x.divide(y, 5, BigFloat::Round::cut);
    EXPECT_EQ(x.to_string(), "0.72251");
}

TEST(big_float_operator_tests, div_test_round_floor) {
    auto x = BigFloat("5c4c");
    auto y = BigFloat("cf00");
    x = x.divide(y, 5, BigFloat::Round::floor);
    EXPECT_EQ(x.to_string(), "0.72251");
}

TEST(big_float_operator_tests, div_test_round_floor_2) {
    auto x = BigFloat("-5c4c");
    auto y = BigFloat("cf00");
    x = x.divide(y, 5, BigFloat::Round::floor);
    EXPECT_EQ(x.to_string(), "-0.72252");
}

TEST(big_float_operator_tests, div_test_round_ceil) {
    auto x = BigFloat("5c4c");
    auto y = BigFloat("cf00");
    x = x.divide(y, 5, BigFloat::Round::ceil);
    EXPECT_EQ(x.to_string(), "0.72252");
}

TEST(big_float_operator_tests, div_test_round_ceil_2) {
    auto x = BigFloat("-5c4c");
    auto y = BigFloat("cf00");
    x = x.divide(y, 5, BigFloat::Round::ceil);
    EXPECT_EQ(x.to_string(), "-0.72251");
}

/// OTHER OPERATORS

TEST(big_float_operator_tests, assignment_operator) {
    auto x = BigFloat("129873.2134");
    auto y = BigFloat("321.654");
    x = y;
    EXPECT_EQ(x.to_string(), "321.654");
}

} // namespace ut
