#include <gtest/gtest.h>
#include "BigDecimal.h"

namespace ut {
using namespace oiak;

//TEST(big_decimal_other_tests, playground) {
//	auto x = BigDecimal();
//	std::cout << "\n" << x.to_science_notation() << "\n";
//}

TEST(big_decimal_other_tests, to_science_notation) {
	auto x = BigDecimal();
	ASSERT_NO_THROW(x.to_science_notation());
	EXPECT_EQ(x.to_science_notation(), "0 * 2 ^ 0");
}

TEST(big_decimal_other_tests, to_string1) {
	auto x = BigDecimal();
	ASSERT_NO_THROW(x.to_string());
	EXPECT_EQ(x.to_string(), "0.0");
}

TEST(big_decimal_other_tests, to_string2) {
	auto x = BigDecimal("123.456");
	EXPECT_EQ(x.to_string(), "123.456");
}

} // namespace ut
