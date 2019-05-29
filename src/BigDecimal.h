#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include "BigInteger.h"

namespace oiak {

class BigDecimal {
	BigInteger significand;
	BigInteger exponent;

public:
	BigDecimal() = default;
	BigDecimal(BigInteger significand, BigInteger exponent, bool sign = false);
	BigDecimal(double value);
	BigDecimal(std::string str);


    bool get_sign() const;
    std::string to_string(std::uint8_t = 16);
};

} // namespace oiak
