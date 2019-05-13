#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include "BigInteger.h"

namespace oiak {

class BigDecimal {
    bool sign = false;
	BigInteger significand;
	BigInteger exponent;

public:
	BigDecimal() = default;
    


    //bool get_sign() const;
    //std::string to_string(std::uint8_t = 16);
};

} // namespace oiak
