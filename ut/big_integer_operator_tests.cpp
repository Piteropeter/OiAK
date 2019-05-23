#include <gtest/gtest.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

TEST(big_integer_operator_tests, sum_of_two_the_same_integers) {
    auto x = BigInteger(123);
    auto y = BigInteger(123);
    x = x + y;
    EXPECT_EQ(x[0], 246);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, sum_of_two_big_integers) {
    auto x = BigInteger(0x0111111111123456);
    auto y = BigInteger(0x0011111111123456);
    x = x + y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 19014178);
    EXPECT_EQ(x[0], 572811436);
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

TEST(big_integer_operator_tests, subtraction_of_two_32bit_integers_result_positive) {
    auto x = BigInteger(0x22222222);
    auto y = BigInteger(0x11111111);
    x = x - y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0x11111111);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_operator_tests, subtraction_of_two_32bit_integers_result_negative) { // TODO: FIX THIS
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
    EXPECT_EQ(x[1], 0x11111111);
    EXPECT_EQ(x[0], 0x11111111);
    EXPECT_FALSE(x.get_sign());
}

// TEST(big_integer_operator_tests, subtraction_of_two_64bit_integers_result_negative) { // TODO: FIX THIS
//	auto x = BigInteger(0x1111111111111111);
//	auto y = BigInteger(0x2222222222222222);
//	x = x - y;
//	EXPECT_EQ(x.size(), 2);
//	EXPECT_EQ(x[0], 0x1111111111111111);
//	EXPECT_TRUE(x.get_sign());
//}

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

/// DIVIDING

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

// TEST(big_integer_operator_tests, ultimate_big_integer_test) {
//	auto x = BigInteger("1234567890987654321");
//	auto y = BigInteger("9999999999999999999");
//	auto z = x * y;
//
//	EXPECT_EQ(z.to_string(), "12345678909876543208765432109012345679");
//}

TEST(big_integer_helper_tests, compare_storages) {
    auto x = BigInteger(256);
    auto y = BigInteger(-356);
	EXPECT_EQ(x.compareStorage(y), -1);

	x = BigInteger(556);
    y = BigInteger(-356);
    EXPECT_EQ(x.compareStorage(y), 1);

	x = BigInteger(256);
    y = BigInteger(256);
    EXPECT_EQ(x.compareStorage(y), 0);
}

} // namespace ut
