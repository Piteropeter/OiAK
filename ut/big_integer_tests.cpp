#include <gtest/gtest.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

TEST(big_integer_tests, big_integer_default_constructor) {
	EXPECT_NO_THROW(BigInteger());
}

TEST(big_integer_tests, big_integer_0_constructor) {
	auto x = BigInteger(0);
	EXPECT_EQ(x.get_value(), "0");
	EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int8min_constructor) {
	auto x = BigInteger(INT8_MIN);
	EXPECT_EQ(x.get_value(), "-128");
	EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int8max_constructor) {
	auto x = BigInteger(INT8_MAX);
	EXPECT_EQ(x.get_value(), "127");
	EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint8max_constructor) {
	auto x = BigInteger(UINT8_MAX);
	EXPECT_EQ(x.get_value(), "255");
	EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int16min_constructor) {
	auto x = BigInteger(INT16_MIN);
	EXPECT_EQ(x.get_value(), "-32768");
	EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int16max_constructor) {
	auto x = BigInteger(INT16_MAX);
	EXPECT_EQ(x.get_value(), "32767");
	EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint16max_constructor) {
	auto x = BigInteger(UINT16_MAX);
	EXPECT_EQ(x.get_value(), "65535");
	EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int32min_constructor) {
	auto x = BigInteger(INT32_MIN);
	EXPECT_EQ(x.get_value(), "-2147483648");
	EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_tests, big_integer_int32max_constructor) {
	auto x = BigInteger(INT32_MAX);
	EXPECT_EQ(x.get_value(), "2147483647");
	EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_uint32max_constructor) {
	auto x = BigInteger(UINT32_MAX);
	EXPECT_EQ(x.get_value(), "4294967295");
	EXPECT_FALSE(x.get_sign());
}

//TEST(big_integer_tests, big_integer_int64min_constructor) {
//	auto x = BigInteger(INT64_MIN);
//	EXPECT_EQ(x.get_value(), "-9223372036854775808");
//	EXPECT_TRUE(x.get_sign());
//}

//TEST(big_integer_tests, big_integer_int64max_constructor) {
//	auto x = BigInteger(INT64_MAX);
//	EXPECT_EQ(x.get_value(), "9223372036854775807");
//	EXPECT_FALSE(x.get_sign());
//}

//TEST(big_integer_tests, big_integer_uint64max_constructor) {
//	auto x = BigInteger(UINT64_MAX);
//	EXPECT_EQ(x.get_value(), "18446744073709551615");
//	EXPECT_FALSE(x.get_sign());
//}

TEST(big_integer_tests, big_integer_sum_of_two_the_same_integers) {
	auto x = BigInteger(123);
	auto y = BigInteger(123);
	x = x + y;
	EXPECT_EQ(x.get_value(), "246");
	EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_sum_of_two_big_integers) {
	auto x = BigInteger(0x0111111111123456);
	auto y = BigInteger(0x0011111111123456);
	x = x + y;
	//EXPECT_EQ(x.get_value(), "");
	EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_tests, big_integer_sum_of_two_very_big_integers) {
	auto x = BigInteger(0xffffffffffffffff);
	auto y = BigInteger(0xffffffffffffffff);
	x = x + y;
	//EXPECT_EQ(x.get_value(), "");
	EXPECT_FALSE(x.get_sign());
}



//TEST(big_integer_tests, ultimate_big_integer_test) {
//	auto x = BigInteger("1234567890987654321");
//	auto y = BigInteger("9999999999999999999");
//	auto z = x * y;
//
//	EXPECT_EQ(z.get_value(), "12345678909876543208765432109012345679");
//}

}
