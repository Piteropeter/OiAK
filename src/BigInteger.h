#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

namespace oiak {

class BigInteger {
    bool sign = false;
    std::vector<std::uint32_t> storage = std::vector<std::uint32_t>(1, 0);
	void normalize();

public:
    BigInteger() = default;
    BigInteger(std::int32_t);
    BigInteger(std::uint32_t);
    BigInteger(std::int64_t);
    BigInteger(std::uint64_t);
	BigInteger(const std::vector<std::uint32_t>&, bool = false);
	BigInteger(std::vector<std::uint32_t>::const_iterator, std::vector<std::uint32_t>::const_iterator, bool = false);
    // BigInteger(std::string); // TODO: ADD IT LATER

    std::uint32_t operator[](std::size_t i);
    const std::uint32_t operator[](std::size_t i) const;
    BigInteger& operator=(const BigInteger& b);
    BigInteger& operator+(const BigInteger& b);
    BigInteger& operator-(const BigInteger& b);
    BigInteger& operator*(const BigInteger& b);
    BigInteger& operator/(const BigInteger& b);
	//BigInteger& operator<<(std::uint64_t);
	//BigInteger& operator>>(std::uint64_t);
    bool operator<(const BigInteger& b) const;
    bool operator>(const BigInteger& b) const;
    // bool operator<=(const BigInteger& b) const;
    // bool operator>=(const BigInteger& b) const;
    // bool operator==(const BigInteger& b) const;


    bool get_sign() const;
    std::size_t size() const;
    std::string to_string(std::uint8_t = 16);
};

} // namespace oiak
