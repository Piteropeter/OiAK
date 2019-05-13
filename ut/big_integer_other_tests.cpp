#include <gtest/gtest.h>
#include "BigInteger.h"

namespace ut {
using namespace oiak;

TEST(big_integer_other_tests, to_string1) {
    auto x = BigInteger(123);
    EXPECT_EQ(x.to_string(), "7b");
}

TEST(big_integer_other_tests, to_string2) {
	auto x = BigInteger(123);
	EXPECT_THROW(x.to_string(10), std::runtime_error);
}

TEST(big_integer_other_tests, size) {
	auto x = BigInteger({1,2,3,4,5});
	EXPECT_EQ(x.size(), 5);
}

TEST(big_integer_other_tests, sign) {
	auto x = BigInteger({1,2,3,4,5});
	x = x * BigInteger(-1);
	EXPECT_TRUE(x.get_sign());
}

} // namespace ut
