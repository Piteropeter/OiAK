#include <gtest/gtest.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

TEST(big_integer_constructor_tests, default_constructor) {
    EXPECT_NO_THROW(BigInteger());
}

TEST(big_integer_constructor_tests, 0_constructor) {
    auto x = BigInteger(0);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, int8min_constructor) {
    auto x = BigInteger(INT8_MIN);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 128);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_constructor_tests, int8max_constructor) {
    auto x = BigInteger(INT8_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 127);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, uint8max_constructor) {
    auto x = BigInteger(UINT8_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 255);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, int16min_constructor) {
    auto x = BigInteger(INT16_MIN);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 32768);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_constructor_tests, int16max_constructor) {
    auto x = BigInteger(INT16_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 32767);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, uint16max_constructor) {
    auto x = BigInteger(UINT16_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 65535);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, int32min_constructor) {
    auto x = BigInteger(INT32_MIN);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 2147483648);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_constructor_tests, int32max_constructor) {
    auto x = BigInteger(INT32_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 2147483647);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, uint32max_constructor) {
    auto x = BigInteger(UINT32_MAX);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 4294967295);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, int32_0_constructor) {
    auto x = BigInteger(int32_t(0));
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, uint32_0_constructor) {
    auto x = BigInteger(int32_t(0));
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, int32_default_constructor) {
    auto x = BigInteger(0);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, uint32_default_constructor) {
    auto x = BigInteger(0u);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, int64min_constructor) {
    auto x = BigInteger(INT64_MIN);
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[0], 2147483648);
    EXPECT_EQ(x[1], 0);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_constructor_tests, int64max_constructor) {
    auto x = BigInteger(INT64_MAX);
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[0], 2147483647);
    EXPECT_EQ(x[1], 4294967295);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, uint64max_constructor) {
    auto x = BigInteger(UINT64_MAX);
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 4294967295);
    EXPECT_EQ(x[0], 4294967295);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, int64_0_constructor) {
    auto x = BigInteger(int64_t(0));
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, uint64_0_constructor) {
    auto x = BigInteger(uint64_t(0));
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, int64_default_constructor) {
    auto x = BigInteger(0);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, uint64_default_constructor) {
    auto x = BigInteger(0u);
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, vector_constructor) {
    std::vector<std::uint32_t> storage = {0x00000001, 0x000000002, 0x00000003};
    auto x = BigInteger(storage, true);
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[2], 1);
    EXPECT_EQ(x[1], 2);
    EXPECT_EQ(x[0], 3);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_constructor_tests, iterator_constructor) {
    std::vector<std::uint32_t> storage = {0x00000001, 0x000000002, 0x00000003};
    auto begin = ++storage.begin();
    auto end = storage.end();
    auto x = BigInteger(begin, end, true);
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 2);
    EXPECT_EQ(x[0], 3);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_constructor_tests, string_constructor1) {

    auto x = BigInteger("123");
    EXPECT_EQ(x.size(), 1);
    EXPECT_EQ(x[0], 0x123);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, string_constructor2) {

    auto x = BigInteger("1234567890");
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[1], 0x12);
    EXPECT_EQ(x[0], 0x34567890);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_integer_constructor_tests, string_constructor3) {

    auto x = BigInteger("-ffffffffffffffffffffffff");
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[2], 0xffffffff);
    EXPECT_EQ(x[1], 0xffffffff);
    EXPECT_EQ(x[0], 0xffffffff);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_constructor_tests, string_constructor4) {

    auto x = BigInteger("-fffffffffffffffffffffff");
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[2], 0xfffffff);
    EXPECT_EQ(x[1], 0xffffffff);
    EXPECT_EQ(x[0], 0xffffffff);
    EXPECT_TRUE(x.get_sign());
}

TEST(big_integer_constructor_tests, string_constructor5) {

    auto x = BigInteger("-fffffffffffffffffffffffff");
    EXPECT_EQ(x.size(), 4);
    EXPECT_EQ(x[3], 0xf);
    EXPECT_EQ(x[2], 0xffffffff);
    EXPECT_EQ(x[1], 0xffffffff);
    EXPECT_EQ(x[0], 0xffffffff);
    EXPECT_TRUE(x.get_sign());
}

} // namespace ut
