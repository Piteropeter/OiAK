#include <gtest/gtest.h>
#include "BigFloat.h"

namespace ut {
using namespace oiak;

TEST(big_float_other_tests, sign) {
    auto x = BigFloat("123.456");
    EXPECT_FALSE(x.get_sign());
    x = BigFloat("-123.456");
    EXPECT_TRUE(x.get_sign());
}

TEST(big_float_other_tests, to_exponential_notation1) {
    auto x = BigFloat();
    ASSERT_NO_THROW(x.to_exponential_notation());
    EXPECT_EQ(x.to_exponential_notation(), "0 * 2 ^ 0");
}

TEST(big_float_other_tests, to_exponential_notation2) {
    auto x = BigFloat("-452345.4567");
    ASSERT_NO_THROW(x.to_exponential_notation());
    EXPECT_EQ(x.to_exponential_notation(), "-4523454567 * 2 ^ -10");
}

TEST(big_float_other_tests, to_string1) {
    auto x = BigFloat();
    ASSERT_NO_THROW(x.to_string());
    EXPECT_EQ(x.to_string(), "0");
}

TEST(big_float_other_tests, to_string2) {
    auto x = BigFloat("0.00456");
    EXPECT_EQ(x.to_string(), "0.00456");
}

TEST(big_float_other_tests, to_string3) {
    auto x = BigFloat("12300.0");
    EXPECT_EQ(x.to_string(), "12300");
}

TEST(big_float_other_tests, to_string4) {
    auto x = BigFloat("123.456");
    EXPECT_EQ(x.to_string(), "123.456");
}

TEST(big_float_other_tests, to_string5) {
    auto x = BigFloat("0.456");
    EXPECT_EQ(x.to_string(), "0.456");
}

} // namespace ut
