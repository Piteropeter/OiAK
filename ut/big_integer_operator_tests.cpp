#include <gtest/gtest.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

/// SUM

TEST(big_integer_operator_tests, sum_of_two_the_same_integers) {
    auto x = BigInteger(123);
    auto y = BigInteger(123);
    x = x + y;
    EXPECT_EQ(x[0], 246);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, sum_of_two_big_integers) {
    auto x = BigInteger(0x0111111111123456);
    auto y = BigInteger(0x0011111111122222);
    x = x + y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 19014178);
    EXPECT_EQ(x[0], 572806776);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, sum_of_two_very_big_integers) {
    auto x = BigInteger(0xffffffffffffffff);
    auto y = BigInteger(0xffffffffffffffff);
    x = x + y;
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[2], 1);
    EXPECT_EQ(x[1], 4294967295);
    EXPECT_EQ(x[0], 4294967294);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, sum_of_two_integers_left_bigger) {
    auto x = BigInteger(0xffffffffffffffff);
    auto y = BigInteger(0xffffffff);
    x = x + y;
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[2], 1);
    EXPECT_EQ(x[1], 0);
    EXPECT_EQ(x[0], 4294967294);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, sum_of_two_integers_right_bigger) {
    auto x = BigInteger(0xffffffff);
    auto y = BigInteger(0xffffffffffffffff);
    x = x + y;
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[2], 1);
    EXPECT_EQ(x[1], 0);
    EXPECT_EQ(x[0], 4294967294);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, sum_of_positive_and_negative) {
    auto x = BigInteger(123);
    auto y = BigInteger(-123);
    x = x + y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
}

TEST(big_integer_operator_tests, sum_of_positive_and_negative_smaller) {
    auto x = BigInteger(123);
    auto y = BigInteger(-100);
    x = x + y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 23);
}

TEST(big_integer_operator_tests, sum_of_positive_and_negative_bigger) {
    auto x = BigInteger(100);
    auto y = BigInteger(-123);
    x = x + y;
    EXPECT_EQ(x[0], 23);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_operator_tests, sum_of_big_same_positive_and_negative) {
    auto x = BigInteger(0xfffffffffffffff);
    auto y = BigInteger(-0xfffffffffffffff);
    x = x + y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
}

TEST(big_integer_operator_tests, sum_of_big_positive_and_negative_smaller) {
    auto x = BigInteger(0xfffffffffffffff);
    auto y = BigInteger(-0xffffffffffffff);
    x = x + y;
    EXPECT_EQ(x[1], 251658240);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, sum_of_big_positive_and_negative_bigger) {
    auto x = BigInteger(0xffffffffffffff);
    auto y = BigInteger(-0xfffffffffffffff);
    x = x + y;
    EXPECT_EQ(x[1], 251658240); // git
    EXPECT_EQ(x[0], 0);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_operator_tests, sum_of_negative_and_one) {
    auto x = BigInteger("-10");
    auto y = BigInteger(1);
    x = x + y;
    EXPECT_EQ(x.to_string(), "-f");
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_operator_tests, ultimate_sum) {
    auto x = BigInteger("123456789abcdef0fedcba987654321");
    auto y = BigInteger("fffffffffffffffffffffffffffffff");
    auto z = x + y;

    EXPECT_EQ(z.to_string(), "1123456789abcdef0fedcba987654320");
}

/// SUBTRACTION

TEST(big_integer_operator_tests, subtraction_of_two_32bit_integers_result_positive) {
    auto x = BigInteger(0x22222222);
    auto y = BigInteger(0x11111111);
    x = x - y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0x11111111);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, subtraction_of_two_32bit_integers_result_negative) {
    auto x = BigInteger(0x11111111);
    auto y = BigInteger(0x22222222);
    x = x - y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0x11111111);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_operator_tests, subtraction_of_two_64bit_integers_result_positive) {
    auto x = BigInteger(0x2222222222222222);
    auto y = BigInteger(0x1111111111111111);
    x = x - y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[0], 0x11111111);
    EXPECT_EQ(x[1], 0x11111111);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, subtraction_of_two_64bit_integers_result_negative) {
    auto x = BigInteger(0x1111111111111111);
    auto y = BigInteger(0x2222222222222222);
    x = x - y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[0], 286331153);
    EXPECT_EQ(x[1], 286331153);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_operator_tests, subtraction_of_positive_and_negative) {
    auto x = BigInteger(0x1111111111112222);
    auto y = BigInteger(-0x1111111111111111);
    x = x - y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 572662306);
    EXPECT_EQ(x[0], 572666675);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, subtraction_of_negative_and_positive) {
    auto x = BigInteger(-0x1111111111112222);
    auto y = BigInteger(0x1111111111111111);
    x = x - y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 572662306);
    EXPECT_EQ(x[0], 572666675);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_operator_tests, subtraction_to_zero) {
    auto x = BigInteger(4);
    auto y = BigInteger(4);
    x = x - y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, different_sizes_subtraction) {
    auto x = BigInteger(0x123000000000);
    auto y = BigInteger(0x123);
    x = x - y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 0x122f);
    EXPECT_EQ(x[0], 0xfffffedd);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, ultimate_subtraction) {
    auto x = BigInteger("123456789abcdef0fedcba987654321");
    auto y = BigInteger("fffffffffffffffffffffffffffffff");
    auto z = x - y;

    EXPECT_EQ(z.to_string(), "-edcba9876543210f0123456789abcde");
}

TEST(big_integer_operator_tests, subtraction_ultimate_and_small) {
    auto x = BigInteger("123456789abcdef0fedcba987654321");
    auto y = BigInteger("f");
    auto z = x - y;

    EXPECT_EQ(z.to_string(), "123456789abcdef0fedcba987654312");
}

/// MULTIPLYING

TEST(big_integer_operator_tests, multiplying_two_32bit_integers) {
    auto x = BigInteger(0x8ab);
    auto y = BigInteger(0xb78);
    x = x * y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0x636928);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, multiplying_two_32bit_integers_result_positive) {
    auto x = BigInteger(0xffffffff);
    auto y = BigInteger(0xffffffff);
    x = x * y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 0xfffffffe);
    EXPECT_EQ(x[0], 0x00000001);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, multiplying_two_32bit_integers_result_negative) {
    auto x = BigInteger(-1);
    auto y = BigInteger(0xffffffff);
    x = x * y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0xffffffff);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_operator_tests, multiplying_two_64bit_integers_result_positive) {
    auto x = BigInteger(0xffffffffffffffff);
    auto y = BigInteger(0xffffffffffffffff);
    x = x * y;
    EXPECT_EQ(x.size(), 4);
    EXPECT_EQ(x[3], 0xffffffff);
    EXPECT_EQ(x[2], 0xfffffffe);
    EXPECT_EQ(x[1], 0x00000000);
    EXPECT_EQ(x[0], 0x00000001);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, multiplying_two_64bit_integers_result_negative) {
    auto x = BigInteger(INT64_MIN);
    auto y = BigInteger(UINT64_MAX);
    x = x * y;
    EXPECT_EQ(x.size(), 4);
    EXPECT_EQ(x[3], 0x7fffffff);
    EXPECT_EQ(x[2], 0xffffffff);
    EXPECT_EQ(x[1], 0x80000000);
    EXPECT_EQ(x[0], 0x00000000);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_operator_tests, ultimate_multiplying) {
    auto x = BigInteger("123456789abcdef0fedcba987654321");
    auto y = BigInteger("fffffffffffffffffffffffffffffff");
    auto z = x * y;

    EXPECT_EQ(z.to_string(), "123456789abcdef0fedcba987654320edcba9876543210f0123456789abcdf");
}

/// DIVIDING

TEST(big_integer_operator_tests, simple_division) {
    auto x = BigInteger("ffffffffffffffffffffff");
    auto y = BigInteger("222222222");
    auto z = x / y;

    EXPECT_EQ(z.to_string(), "78000000078000");
}

TEST(big_integer_operator_tests, division_big_dividend_small_divisor) {
    auto x = BigInteger("ffffffffffffffffffffff");
    auto y = BigInteger("1");
    auto z = x / y;

    EXPECT_EQ(z.to_string(), "ffffffffffffffffffffff");
}

TEST(big_integer_operator_tests, division_same_dividend_and_divisor) {
    auto x = BigInteger("ffffffffffffffffffffff");
    auto y = BigInteger("ffffffffffffffffffffff");
    auto z = x / y;

    EXPECT_EQ(z.to_string(), "1");
}

TEST(big_integer_operator_tests, division_negative_dividend_positive_divisor) {
    auto x = BigInteger("-ffffffffffffffffffffff");
    auto y = BigInteger("ffffffffffffffffffffff");
    auto z = x / y;

    EXPECT_EQ(z.to_string(), "-1");
}

TEST(big_integer_operator_tests, division_positive_dividend_negative_divisor) {
    auto x = BigInteger("ffffffffffffffffffffff");
    auto y = BigInteger("-ffffffffffffffffffffff");
    auto z = x / y;

    EXPECT_EQ(z.to_string(), "-1");
}

TEST(big_integer_operator_tests, division_negative_dividend_negative_divisor) {
    auto x = BigInteger("-ffffffffffffffffffffff");
    auto y = BigInteger("-ffffffffffffffffffffff");
    auto z = x / y;

    EXPECT_EQ(z.to_string(), "1");
}

TEST(big_integer_operator_tests, ultimate_dividing) {
    auto x = BigInteger("123456789abcdef0fedcba987654321");
    auto y = BigInteger("fffffffffffffffffffffffffffffff");
    auto z = y / x;

    EXPECT_EQ(z.to_string(), "e");
}

/// OTHER OPERATORS

TEST(big_integer_operator_tests, compare_operators_test1) {
    auto x = BigInteger(0xffffffffffffffff);
    auto y = BigInteger(0xffffffffffffffff);

    EXPECT_FALSE(x > y);
    EXPECT_FALSE(x < y);
}

TEST(big_integer_operator_tests, compare_operators_test2) {
    auto x = BigInteger(0xffffffff);
    auto y = BigInteger(0xffffffffffffffff);

    EXPECT_TRUE(x < y);
    EXPECT_FALSE(x > y);
}

TEST(big_integer_operator_tests, compare_operators_test3) {
    auto x = BigInteger(-15);
    auto y = BigInteger(15);

    EXPECT_FALSE(x > y);
    EXPECT_TRUE(x < y);
}

TEST(big_integer_operator_tests, compare_operators_test4) {
    auto x = BigInteger(-432);
    auto y = BigInteger(-432);

    EXPECT_TRUE(x == y);
    // EXPECT_FALSE(x != y);
}

TEST(big_integer_operator_tests, compare_operators_test5) {
    auto x = BigInteger(0xffffffffffffffff);
    auto y = BigInteger(0xfffffffffffffffe);

    EXPECT_TRUE(x > y);
    EXPECT_FALSE(x < y);
}

TEST(big_integer_operator_tests, compare_operators_test6) {
    auto x = BigInteger(-18);
    auto y = BigInteger(-1);

    EXPECT_FALSE(x > y);
    EXPECT_TRUE(x < y);
}

TEST(big_integer_operator_tests, shift_left_test) {
    auto x = BigInteger(0x10);
    auto y = x << 1;

	EXPECT_EQ(y[0], 32);
}
TEST(big_integer_operator_tests, shift_left_test_2) {
    auto x = BigInteger(0x10);
    auto y = x << 4;

    EXPECT_EQ(y[0], 256);
}

TEST(big_integer_operator_tests, big_shift_left_test) {
    auto x = BigInteger(0x10);
    auto y = x << 256;

    EXPECT_EQ(y[8], 0x10);
}

TEST(big_integer_operator_tests, big_shift_left_test_2) {
    auto x = BigInteger(0xfffffffffffffff);
    auto y = x << 1;

    EXPECT_EQ(y.to_string(), "1ffffffffffffffe");
}

TEST(big_integer_operator_tests, big_shift_left_test_3) {
    auto x = BigInteger(0xfffffffffffffff);
    auto y = x << 4;

    EXPECT_EQ(y.to_string(), "fffffffffffffff0");
}
TEST(big_integer_operator_tests, big_shift_left_test_4) {
    auto x = BigInteger("1234567890abcdef1234567abcdef");
    auto y = x << 6;

    EXPECT_EQ(y.to_string(), "48d159e242af37bc48d159eaf37bc0");
}


TEST(big_integer_operator_tests, shift_right_test) {
    auto x = BigInteger(0x10);
    auto y = x >> 1;

    EXPECT_EQ(y.to_string(), "8");
}
TEST(big_integer_operator_tests, shift_right_test_2) {
    auto x = BigInteger(0x10);
    auto y = x >> 4;

    EXPECT_EQ(y.to_string(), "1");
}

TEST(big_integer_operator_tests, big_shift_right_test) {
    auto x = BigInteger(0x10);
    auto y = x >> 8;

    EXPECT_EQ(y.to_string(), "0");
}

TEST(big_integer_operator_tests, big_shift_right_test_2) {
    auto x = BigInteger(0x1ffffffffffffffe);
    auto y = x >> 1;

    EXPECT_EQ(y.to_string(), "fffffffffffffff");
}

TEST(big_integer_operator_tests, big_shift_right_test_3) {
    auto x = BigInteger(0xfffffffffffffff0);
    auto y = x >> 4;

    EXPECT_EQ(y.to_string(), "fffffffffffffff");
}

TEST(big_integer_operator_tests, big_shift_right_test_4) {
    auto x = BigInteger("1234567890abcdef1234567abcdef");
    auto y = x >> 6;

    EXPECT_EQ(y.to_string(), "48d159e242af37bc48d159eaf37");
}

} // namespace ut
