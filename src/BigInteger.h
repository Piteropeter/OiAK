#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

namespace oiak {

class BigFloat;

class BigInteger {
    friend BigFloat;

    bool sign = false;
    std::vector<std::uint32_t> storage = std::vector<std::uint32_t>(1, 0);

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
    BigInteger operator+(const BigInteger&);
    BigInteger operator-(const BigInteger&);
    BigInteger operator*(const BigInteger&);
    BigInteger operator/(const BigInteger&);
    bool operator<(const BigInteger&) const;
    bool operator>(const BigInteger&) const;
    bool operator==(const BigInteger&) const;
    bool get_sign() const;
    std::size_t size() const;
    std::string to_string();

private:
    void set_sign(bool);
    BigInteger divide(const BigInteger& b);
    int compareStorage(const std::vector<std::uint32_t>& s1, const std::vector<std::uint32_t>& s2) const;
    std::vector<std::uint32_t> add(const std::vector<std::uint32_t>& s1, const std::vector<std::uint32_t>& s2);
    std::vector<std::uint32_t> subtract(const std::vector<std::uint32_t>& s1, const std::vector<std::uint32_t>& s2);
    bool divmnu(std::vector<std::uint32_t>& q, std::vector<std::uint32_t>& r, const std::vector<std::uint32_t> u, const std::vector<std::uint32_t> v);
    std::uint8_t nlz(std::uint32_t) const;
};
} // namespace oiak
