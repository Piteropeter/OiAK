#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include "BigInteger.h"

namespace oiak {
class BigFloat {
    BigInteger significand;
    BigInteger exponent;

public:
    enum class Round { symetric_even, floor, ceil, cut };

    BigFloat() = default;
    BigFloat(BigInteger significand, BigInteger exponent, bool sign = false);
    BigFloat(double value);
    BigFloat(std::string str);

    BigFloat& operator=(const BigFloat&);
    BigFloat operator+(const BigFloat&);
    BigFloat operator-(const BigFloat&);
    BigFloat operator*(const BigFloat&);
    BigFloat operator/(const BigFloat&);

    BigFloat divide(const BigFloat&, BigInteger, Round = Round::symetric_even);

    bool get_sign() const;
    std::string to_string();
    std::string to_exponential_notation();

private:
    void normalize(BigFloat& b);
};

} // namespace oiak
