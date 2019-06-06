#include <gtest/gtest.h>
#include "BigFloat.h"

namespace ut {
using namespace oiak;

TEST(big_float_constructor_tests, default_constructor) {
    EXPECT_NO_THROW(BigFloat());
}

TEST(big_float_constructor_tests, 0_big_integers_constructor) {
    auto x = BigFloat(0, 0);
    EXPECT_FALSE(x.get_sign());
}

TEST(big_float_constructor_tests, double_constructor1) {
    auto x = BigFloat(0.0);
    EXPECT_FALSE(x.get_sign());
    EXPECT_EQ("0 * 2 ^ 0", x.to_exponential_notation());
}

TEST(big_float_constructor_tests, double_constructor2) {
    auto x = BigFloat(-13.333);
    EXPECT_TRUE(x.get_sign());
    EXPECT_EQ("-1aaa7ef9db22d1 * 2 ^ -31", x.to_exponential_notation());
}

TEST(big_float_constructor_tests, double_constructor3) {
    auto x = BigFloat(1.0);
    EXPECT_FALSE(x.get_sign());
    EXPECT_EQ("1 * 2 ^ 0", x.to_exponential_notation());
}

TEST(big_float_constructor_tests, double_constructor4) {
    auto x = BigFloat(0.0009765625);
    EXPECT_FALSE(x.get_sign());
    EXPECT_EQ("1 * 2 ^ -a", x.to_exponential_notation());
}

TEST(big_float_constructor_tests, string_constructor1) {
    auto x = BigFloat("-13.333");
    EXPECT_TRUE(x.get_sign());
    EXPECT_EQ("-13333 * 2 ^ -c", x.to_exponential_notation());
}

TEST(big_float_constructor_tests, string_constructor2) {
    auto x = BigFloat("0.333");
    EXPECT_FALSE(x.get_sign());
    EXPECT_EQ("333 * 2 ^ -c", x.to_exponential_notation());
}

TEST(big_float_constructor_tests, string_constructor3) {
    auto x = BigFloat("123");
    EXPECT_FALSE(x.get_sign());
    EXPECT_EQ("123 * 2 ^ 0", x.to_exponential_notation());
}

TEST(big_float_constructor_tests, string_constructor4) {
    auto x = BigFloat("-0.0008");
    EXPECT_TRUE(x.get_sign());
    EXPECT_EQ("-1 * 2 ^ -d", x.to_exponential_notation());
}

TEST(big_float_constructor_tests, string_constructor5) {
    auto x = BigFloat("20");
    EXPECT_FALSE(x.get_sign());
    EXPECT_EQ("1 * 2 ^ 5", x.to_exponential_notation());
}

} // namespace ut
