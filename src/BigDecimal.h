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
    enum class Round { symetric_even, floor, ceil, cut };

    BigDecimal() = default;
    BigDecimal(BigInteger significand, BigInteger exponent, bool sign = false);
    BigDecimal(double value);
    BigDecimal(std::string str);

    BigDecimal& operator=(const BigDecimal&);
    BigDecimal operator+(const BigDecimal&);
    BigDecimal operator-(const BigDecimal&);
    BigDecimal operator*(const BigDecimal&);
    BigDecimal operator/(const BigDecimal&);

    BigDecimal divide(const BigDecimal&, BigInteger, Round = Round::symetric_even);

    bool get_sign() const;
    std::string to_string();
    std::string to_exponential_notation();

private:
    void normalize(BigDecimal& b);
};

} // namespace oiak
