#include <gtest/gtest.h>
#include "BigDecimal.h"

namespace ut {
using namespace oiak;

TEST(big_decimal_operator_tests, assignment_operator) {
	auto x = BigDecimal("129873.2134");
	auto y = BigDecimal("321.654");
	x = y;
	//EXPECT_EQ(x.to_string(), "321.654");
}

} // namespace ut
