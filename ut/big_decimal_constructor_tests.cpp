#include <gtest/gtest.h>
#include "BigDecimal.h"

namespace ut {
using namespace oiak;

TEST(big_decimal_constructor_tests, default_constructor) {
	EXPECT_NO_THROW(BigDecimal());
}

TEST(big_decimal_constructor_tests, 0_big_integers_constructor) {
	auto x = BigDecimal(0, 0);
	EXPECT_FALSE(x.get_sign());
}

TEST(big_decimal_constructor_tests, 0_double_constructor) {
	auto x = BigDecimal(-5643223465.65474562345);
	std::cout << "\n" << x.to_string() << "\n";
	//EXPECT_FALSE(x.get_sign());
}

} // namespace ut
