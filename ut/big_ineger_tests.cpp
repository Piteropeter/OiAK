#include <gtest/gtest.h>
#include "Lib.h"

namespace ut {
using namespace oiak;

<<<<<<< HEAD
TEST(big_integer_tests, base10_big_integer_constructor) {
    //auto x = BigInteger<10u>(123);
    auto y = BigInteger<10u>();
}

TEST(big_integer_tests, first_test2) {
    auto x = oiak::Test();
=======
TEST(big_integer_tests, big_integer_constructor) {
    auto x = BigInteger(123);
    auto y = BigInteger();
>>>>>>> First library types
}

}
