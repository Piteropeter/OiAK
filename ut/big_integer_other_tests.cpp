#include <gtest/gtest.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

TEST(big_integer_other_tests, to_string1) {
	auto x = BigInteger(123);
	EXPECT_NO_THROW(x.to_string(10));
}

TEST(big_integer_other_tests, to_string2) {
    auto x = BigInteger(123);
    EXPECT_EQ(x.to_string(10), "123");
}

TEST(big_integer_other_tests, to_string3) {
	auto x = BigInteger(123);
	EXPECT_EQ(x.to_string(), "0x7b");
}

TEST(big_integer_other_tests, to_string4) {
    std::vector<std::uint32_t> storage = {1, 2, 3, 4, 5};
    auto x = BigInteger(storage);
    EXPECT_EQ(x.to_string(), "0x100000002000000030000000400000005");
}

TEST(big_integer_other_tests, to_string5) {
    std::vector<std::uint32_t> storage = {1, 2, 3, 4, 5};
    auto x = BigInteger(storage);
    EXPECT_THROW(x.to_string(10), std::runtime_error);
}

TEST(big_integer_other_tests, size) {
    std::vector<std::uint32_t> storage = {1, 2, 3, 4, 5};
    auto x = BigInteger(storage);
    EXPECT_EQ(x.size(), 5);
}

TEST(big_integer_other_tests, sign) {
    std::vector<std::uint32_t> storage = {1, 2, 3, 4, 5};
    auto x = BigInteger(storage);
    x = x * BigInteger(-1);
    EXPECT_TRUE(x.get_sign());
}

} // namespace ut
