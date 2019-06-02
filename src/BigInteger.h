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
    BigInteger(std::string);

    std::uint32_t operator[](std::size_t i);
    const std::uint32_t operator[](std::size_t i) const;
    BigInteger& operator=(const BigInteger&);
    BigInteger& operator+(const BigInteger&);
    BigInteger& operator-(const BigInteger&);
    BigInteger& operator*(const BigInteger&);
    BigInteger& operator/(const BigInteger&);
	//BigInteger& operator<<(std::uint64_t);
	//BigInteger& operator>>(std::uint64_t);
    bool operator<(const BigInteger&) const;
    bool operator>(const BigInteger&) const;
    // bool operator<=(const BigInteger&) const;
    // bool operator>=(const BigInteger&) const;
    // bool operator==(const BigInteger&) const;

	void set_sign(bool);
    bool get_sign() const;
    std::size_t size() const;

    std::string to_string();
private:
    int BigInteger::compareStorage(std::vector<std::uint32_t> s1, std::vector<std::uint32_t> s2);
    std::vector<std::uint32_t> add(std::vector<std::uint32_t>, std::vector<std::uint32_t>);
	// Storage must be greater than subtracted parameter s2
    std::vector<std::uint32_t> subtract(std::vector<std::uint32_t> s1, std::vector<std::uint32_t> s2);
};


} // namespace oiak
