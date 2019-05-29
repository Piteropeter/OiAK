#include <gtest/gtest.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

TEST(big_integer_other_tests, to_string1) {
	auto x = BigInteger(-123);
	EXPECT_EQ(x.to_string(), "-7b");
}

TEST(big_integer_other_tests, to_string2) {
    std::vector<std::uint32_t> storage = {1, 2, 3, 4, 5};
    auto x = BigInteger(storage);
    EXPECT_EQ(x.to_string(), "100000002000000030000000400000005");
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
