#include <gtest/gtest.h>
#include "BigDecimal.h"

namespace ut {
using namespace oiak;

//TEST(big_decimal_other_tests, playground) {
//	auto x = BigDecimal();
//	std::cout << "\n" << x.to_string() << "\n";
//}

TEST(big_decimal_other_tests, to_string1) {
	auto x = BigDecimal();
	EXPECT_NO_THROW(x.to_string());
}

} // namespace ut
