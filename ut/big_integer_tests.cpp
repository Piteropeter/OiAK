#include <gtest/gtest.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

TEST(big_integer_tests, big_integer_default_constructor) {
    EXPECT_NO_THROW(BigInteger());
}

TEST(big_integer_tests, big_integer_0_constructor) {
    auto x = BigInteger(0);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int8min_constructor) {
    auto x = BigInteger(INT8_MIN);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 128);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int8max_constructor) {
    auto x = BigInteger(INT8_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 127);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint8max_constructor) {
    auto x = BigInteger(UINT8_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 255);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int16min_constructor) {
    auto x = BigInteger(INT16_MIN);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 32768);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int16max_constructor) {
    auto x = BigInteger(INT16_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 32767);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint16max_constructor) {
    auto x = BigInteger(UINT16_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 65535);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int32min_constructor) {
    auto x = BigInteger(INT32_MIN);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 2147483648);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int32max_constructor) {
    auto x = BigInteger(INT32_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 2147483647);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint32max_constructor) {
    auto x = BigInteger(UINT32_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 4294967295);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int32_0_constructor) {
    auto x = BigInteger(int32_t(0));
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint32_0_constructor) {
    auto x = BigInteger(int32_t(0));
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int32_default_constructor) {
    auto x = BigInteger(0);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint32_default_constructor) {
    auto x = BigInteger(0u);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int64min_constructor) {
    auto x = BigInteger(INT64_MIN);
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 2147483648);
    EXPECT_EQ(x[0], 0);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int64max_constructor) {
    auto x = BigInteger(INT64_MAX);
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 2147483647);
    EXPECT_EQ(x[0], 4294967295);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint64max_constructor) {
    auto x = BigInteger(UINT64_MAX);
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 4294967295);
    EXPECT_EQ(x[0], 4294967295);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int64_0_constructor) {
    auto x = BigInteger(int64_t(0));
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint64_0_constructor) {
    auto x = BigInteger(uint64_t(0));
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int64_default_constructor) {
    auto x = BigInteger(0);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint64_default_constructor) {
    auto x = BigInteger(0u);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_sum_of_two_the_same_integers) {
    auto x = BigInteger(123);
    auto y = BigInteger(123);
    x = x + y;
    EXPECT_EQ(x.to_string(), "246");
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_sum_of_two_big_integers) {
    auto x = BigInteger(0x0111111111123456);
    auto y = BigInteger(0x0011111111123456);
    x = x + y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 19014178);
    EXPECT_EQ(x[0], 572811436);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_sum_of_two_very_big_integers) {
    auto x = BigInteger(0xffffffffffffffff);
    auto y = BigInteger(0xffffffffffffffff);
    x = x + y;
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[2], 1);
    EXPECT_EQ(x[1], 4294967295);
    EXPECT_EQ(x[0], 4294967294);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_sum_of_two_integers_left_bigger) {
    auto x = BigInteger(0xffffffffffffffff);
    auto y = BigInteger(0xffffffff);
    x = x + y;
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[2], 1);
    EXPECT_EQ(x[1], 0);
    EXPECT_EQ(x[0], 4294967294);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_sum_of_two_integers_right_bigger) {
    auto x = BigInteger(0xffffffff);
    auto y = BigInteger(0xffffffffffffffff);
    x = x + y;
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[2], 1);
    EXPECT_EQ(x[1], 0);
    EXPECT_EQ(x[0], 4294967294);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_subtraction_of_two_32bit_integers_result_positive) {
    auto x = BigInteger(0x22222222);
    auto y = BigInteger(0x11111111);
    x = x - y;
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0x11111111);
    EXPECT_FALSE(x.get_sign());
}

// TEST(big_integer_tests, big_integer_subtraction_of_two_32bit_integers_result_negative) { // TODO: FIX THIS
//	auto x = BigInteger(0x11111111);
//	auto y = BigInteger(0x22222222);
//	x = x - y;
//	EXPECT_EQ(x.size(), 1);
//	EXPECT_EQ(x[0], 0x11111111);
//	EXPECT_TRUE(x.get_sign());
//}

TEST(big_integer_tests, big_integer_subtraction_of_two_64bit_integers_result_positive) {
    auto x = BigInteger(0x2222222222222222);
    auto y = BigInteger(0x1111111111111111);
    x = x - y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 0x11111111);
    EXPECT_EQ(x[0], 0x11111111);
    EXPECT_FALSE(x.get_sign());
}

// TEST(big_integer_tests, big_integer_subtraction_of_two_64bit_integers_result_negative) { // TODO: FIX THIS
//	auto x = BigInteger(0x1111111111111111);
//	auto y = BigInteger(0x2222222222222222);
//	x = x - y;
//	EXPECT_EQ(x.size(), 2);
//	EXPECT_EQ(x[0], 0x1111111111111111);
//	EXPECT_TRUE(x.get_sign());
//}

TEST(big_integer_tests, big_integer_multiplying_two_32bit_integers) {
    auto x = BigInteger(0x8ab);
    auto y = BigInteger(0xb78);
    x = x * y;
    // EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0x636928);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_multiplying_two_32bit_integers_result_positive) {
    auto x = BigInteger(0xffffffff);
    auto y = BigInteger(0xffffffff);
    x = x * y;
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 0xfffffffe);
    EXPECT_EQ(x[0], 0x00000001);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_multiplying_two_32bit_integers_result_negative) {
    auto x = BigInteger(0xffffffff);
    auto y = BigInteger(std::int64_t(0xffffffff) * -1);
    x = x * y;
    // EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 0xfffffffe);
    EXPECT_EQ(x[0], 0x00000001);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_tests, big_integer_multiplying_two_64bit_integers_result_positive) {
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

TEST(big_integer_tests, big_integer_multiplying_two_64bit_integers_result_negative) {
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

// TEST(big_integer_tests, ultimate_big_integer_test) {
//	auto x = BigInteger("1234567890987654321");
//	auto y = BigInteger("9999999999999999999");
//	auto z = x * y;
//
//	EXPECT_EQ(z.to_string(), "12345678909876543208765432109012345679");
//}

} // namespace ut
