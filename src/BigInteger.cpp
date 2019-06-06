#include "BigInteger.h"

namespace oiak {

void normalize(std::vector<std::uint32_t>& store) {
    if(store.size() > 1 && store.back() == 0) {
        auto it = store.begin() + store.size() - 1;
        while(*it == 0 && it != store.end() && store.size() > 1) {
            store.erase(it);
            it = store.begin() + store.size() - 1;
        }
    }
}

// CONSTRUCTORS

BigInteger::BigInteger(std::int32_t value) {
    if(value < 0) {
        sign = true;
        value *= -1;
    }
    storage[0] = static_cast<std::uint32_t>(value);
}

BigInteger::BigInteger(std::uint32_t value) {
    storage[0] = static_cast<std::uint32_t>(value);
}

BigInteger::BigInteger(std::int64_t value) {
    if(value < static_cast<std::int64_t>(INT32_MAX) && value > -static_cast<std::int64_t>(INT32_MAX))
        *this = BigInteger(static_cast<std::int32_t>(value));
    else {
        if(value < 0) {
            sign = true;
            value *= -1;
        }
        if(value > static_cast<std::int64_t>(INT32_MAX) || value < -static_cast<std::int64_t>(INT32_MAX)) {
            storage.resize(2);
            storage[1] = value >> 32;
        }
        storage[0] = value << 32 >> 32;
    }
}

BigInteger::BigInteger(std::uint64_t value) {
    if(value < static_cast<std::uint64_t>(UINT32_MAX))
        *this = BigInteger(static_cast<std::uint32_t>(value));
    else {
        if(value > UINT32_MAX) {
            storage.resize(2);
            storage[1] = value >> 32;
        }
        storage[0] = value << 32 >> 32;
    }
}

BigInteger::BigInteger(const std::vector<std::uint32_t>& storage, bool sign) {
    this->storage = std::vector<std::uint32_t>(storage.rbegin(), storage.rend());
    this->sign = sign;
}

BigInteger::BigInteger(std::vector<std::uint32_t>::const_iterator begin, std::vector<std::uint32_t>::const_iterator end, bool sign) {
    auto rbegin = static_cast<std::vector<std::uint32_t>::const_reverse_iterator>(begin);
    auto rend = static_cast<std::vector<std::uint32_t>::const_reverse_iterator>(end);
    this->storage = std::vector<std::uint32_t>(rend, rbegin);
    this->sign = sign;
}

BigInteger::BigInteger(std::string str) {
    if(str[0] == '-') {
        sign = true;
        str = str.substr(1, str.size());
    }

    std::vector<std::uint32_t> storage;
    std::size_t i = str.size(), j = str.size() > 7 ? str.size() - 8 : 0;
    for(auto x = 0u; x < str.size() / 8; x++, i -= 8, j -= 8)
        storage.push_back(std::stoul(str.substr(j, 8), 0, 16));

    if(str.size() % 8)
        storage.push_back(std::stoul(str.substr(0, i), 0, 16));

    this->storage = storage;
}

// OPERATORS

std::uint32_t BigInteger::operator[](std::size_t i) {
    return storage[i];
}

const std::uint32_t BigInteger::operator[](std::size_t i) const {
    return storage[i];
}

BigInteger& BigInteger::operator=(const BigInteger& b) {
    sign = b.sign;
    storage = b.storage;
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger& b) {
    BigInteger new_integer = *this;
    if((!new_integer.sign && !b.sign) || (new_integer.sign && b.sign)) {
        new_integer.storage = add(new_integer.storage, b.storage);
        return new_integer;
    }

    auto cmp = compareStorage(new_integer.storage, b.storage);
    if(cmp == 0) {
        new_integer.storage.clear();
        new_integer.storage.push_back(0);
        new_integer.sign = false;
    } else {
        if(cmp > 0) {
            new_integer.storage = subtract(new_integer.storage, b.storage);
        } else {
            new_integer.storage = subtract(b.storage, new_integer.storage);
            new_integer.sign = b.sign;
        }
    }
    return new_integer;
}

BigInteger BigInteger::operator-(const BigInteger& b) {
    BigInteger new_integer = *this;
    if(b.sign != new_integer.sign) {
        new_integer.storage = add(new_integer.storage, b.storage);
    } else {
        auto cmp = compareStorage(new_integer.storage, b.storage);
        if(cmp == 0) {
            new_integer.storage.resize(1);
            new_integer.storage[0] = 0;
            new_integer.sign = false;
            return new_integer;
        } else {
            if(cmp > 0) {
                new_integer.storage = subtract(new_integer.storage, b.storage);
            } else {
                new_integer.storage = subtract(b.storage, new_integer.storage);
                new_integer.sign = !new_integer.sign;
            }
        }
    }

    normalize(new_integer.storage);
    return new_integer;
}

BigInteger BigInteger::operator*(const BigInteger& b) {
    BigInteger new_integer = *this;
    std::vector<std::uint64_t> tmp(new_integer.storage.size() + b.storage.size(), 0);

    for(auto i = 0u; i < new_integer.storage.size(); i++) {
        for(auto j = 0u; j < b.storage.size(); j++) {
            tmp[i + j] += static_cast<std::uint64_t>(new_integer.storage[i]) * static_cast<std::uint64_t>(b.storage[j]);
            if(tmp[i + j] > UINT32_MAX) {
                tmp[i + j + 1] += tmp[i + j] >> 32;
                tmp[i + j] = tmp[i + j] << 32 >> 32;
            }
        }
    }

    new_integer.storage.resize(tmp.size());
    for(auto i = 0u; i < new_integer.storage.size(); i++) {
        new_integer.storage[i] = static_cast<std::uint32_t>(tmp[i]);
    }

    if(sign && !b.sign || !sign && b.sign)
        new_integer.sign = true;
    else
        new_integer.sign = false;

    normalize(new_integer.storage);
    return new_integer;
}

BigInteger BigInteger::operator/(const BigInteger& b) {
    BigInteger new_integer = *this;
    new_integer.divide(b);
    return new_integer;
}

bool BigInteger::operator<(const BigInteger& b) const {
    if(sign && !b.sign)
        return true;
    else if(!sign && b.sign)
        return false;
    else if(sign == b.sign) {
        auto result = compareStorage(storage, b.storage);
        if(sign) {
            if(result == 1)
                return true;
            else
                return false;
        } else {
            if(result == -1)
                return true;
            else
                return false;
        }
    }
    return false;
}

bool BigInteger::operator>(const BigInteger& b) const {
    if(sign && !b.sign)
        return false;
    else if(!sign && b.sign)
        return true;
    else if(sign == b.sign) {
        auto result = compareStorage(storage, b.storage);
        if(sign) {
            if(result == -1)
                return true;
            else
                return false;
        } else {
            if(result == 1)
                return true;
            else
                return false;
        }
    }
    return false;
}

bool BigInteger::operator==(const BigInteger& b) const {
    if(sign == b.sign && storage.size() == b.storage.size()) {
        for(auto i = 0u; i < storage.size(); i++)
            if(storage[i] != b.storage[i])
                return false;
        return true;
    } else
        return false;
}

// Alters left operand. Returns remainder as new BigInteger.
BigInteger BigInteger::divide(const BigInteger& b) {

    std::uint64_t m = storage.size();
    std::uint64_t n = b.storage.size();

    auto quotient = std::vector<std::uint32_t>(m - n + 1);
    auto r = std::vector<std::uint32_t>(n);

    divmnu(quotient, r, storage, b.storage);

    normalize(quotient);
    storage = quotient;
    sign = (sign || b.sign) && !(sign && b.sign);

    return BigInteger(r);
}

// OTHER FUNCTIONS

void BigInteger::set_sign(bool value) {
    if(value != sign)
        sign = value;
}

bool BigInteger::get_sign() const {
    return sign;
}

std::size_t BigInteger::size() const {
    return storage.size();
}

std::string BigInteger::to_string() {
    std::stringstream ss;
    if(sign)
        ss << '-';

    for(auto it = storage.crbegin(); it != storage.crend(); it++) {
        if(it == storage.crbegin()) {
            ss << std::hex << *it;
            continue;
        }

        if(*it < 0x1)
            ss << '0';
        if(*it < 0x10)
            ss << '0';
        if(*it < 0x100)
            ss << '0';
        if(*it < 0x1000)
            ss << '0';
        if(*it < 0x10000)
            ss << '0';
        if(*it < 0x100000)
            ss << '0';
        if(*it < 0x1000000)
            ss << '0';
        if(*it < 0x10000000)
            ss << '0';
        ss << std::hex << *it;
    }
    return ss.str();
}

// Helper methods
int BigInteger::compareStorage(const std::vector<std::uint32_t>& s1, const std::vector<std::uint32_t>& s2) const {
    auto len1 = s1.size();
    auto len2 = s2.size();

    if(len1 < len2)
        return -1;
    if(len1 > len2)
        return 1;
    int i = (len1 - 1);

    while(i >= 0) {
        uint32_t x = s1[i];
        uint32_t y = s2[i--];

        if(x != y) {
            if(x < y)
                return -1;
            else
                return 1;
        }
    }
    return 0;
}
std::vector<std::uint32_t> BigInteger::add(const std::vector<std::uint32_t>& s1, const std::vector<std::uint32_t>& s2) {
    std::uint64_t tmp = 0;
    bool carry_bit = false;

    auto result = std::vector<std::uint32_t>(s1);

    if(result.size() < s2.size())
        result.resize(s2.size());

    for(auto i = 0u; i < result.size(); i++) {
        if(i < s2.size())
            tmp = static_cast<std::uint64_t>(result[i]) + static_cast<std::uint64_t>(s2[i]);
        else
            tmp = static_cast<std::uint64_t>(result[i]);

        if(carry_bit) {
            tmp++;
            carry_bit = false;
        }

        if(tmp > UINT32_MAX) {
            result[i] = tmp << 32 >> 32;
            if(i + 1 == result.size()) {
                result.resize(result.size() + 1);
            }

            carry_bit = true;

        } else
            result[i] = static_cast<std::uint32_t>(tmp);
    }

    return result;
}

// Assumes s2 smaller than this.storage
std::vector<std::uint32_t> BigInteger::subtract(const std::vector<std::uint32_t>& s1, const std::vector<std::uint32_t>& s2) {
    std::int64_t tmp = 0;
    bool borrow_bit = false;
    auto result = std::vector<std::uint32_t>(s1);

    for(auto i = 0u; i < s1.size(); i++) {
        if(i < s2.size())
            tmp = static_cast<std::int64_t>(s1[i]) - static_cast<std::int64_t>(s2[i]);
        else
            tmp = static_cast<std::int64_t>(s1[i]);

        if(borrow_bit) {
            tmp--;
            borrow_bit = false;
        }

        if(tmp < 0) {
            result[i] = static_cast<std::uint32_t>(tmp);
            borrow_bit = true;
        } else
            result[i] = static_cast<std::uint32_t>(tmp);
    }
    if(borrow_bit && tmp < 0) {
        result.resize(result.size() + 1);
        result[result.size() - 1] = 1;
        sign = true;
    }
    return result;
}

std::uint8_t BigInteger::nlz(std::uint32_t x) const {
    int n;

    if(x == 0)
        return (32);
    n = 0;
    if(x <= 0x0000FFFF) {
        n = n + 16;
        x = x << 16;
    }
    if(x <= 0x00FFFFFF) {
        n = n + 8;
        x = x << 8;
    }
    if(x <= 0x0FFFFFFF) {
        n = n + 4;
        x = x << 4;
    }
    if(x <= 0x3FFFFFFF) {
        n = n + 2;
        x = x << 2;
    }
    if(x <= 0x7FFFFFFF) {
        n = n + 1;
    }
    return n;
}

void divmnu_helper_recursive(uint64_t& quotDigit, const uint64_t& b, std::vector<uint32_t>& normalDivisor, const size_t& divisorLen,
                             uint64_t& remainderDigit, std::vector<uint32_t>& normalDividend, const int32_t& j) {
    if(quotDigit >= b || quotDigit * normalDivisor[divisorLen - 2] > b * remainderDigit + normalDividend[j + divisorLen - 2]) {
        quotDigit = quotDigit - 1;
        remainderDigit = remainderDigit + normalDivisor[divisorLen - 1];
        if(remainderDigit < b)
            divmnu_helper_recursive(quotDigit, b, normalDivisor, divisorLen, remainderDigit, normalDividend, j);
    }
}

/*
This is a fairly precise implementation of Knuth's Algorithm D, for a
binary computer with base b = 2**32
*/
bool BigInteger::divmnu(std::vector<std::uint32_t>& quotient, std::vector<std::uint32_t>& remainder,
                        const std::vector<std::uint32_t> divident, const std::vector<std::uint32_t> divisor) {

    std::size_t dividentLen = divident.size();
    std::size_t divisorLen = divisor.size();

    constexpr std::uint64_t b = 4294967296;
    auto normalDividend = std::vector<std::uint32_t>(dividentLen + 1);
    auto normalDivisor = std::vector<std::uint32_t>(divisorLen);
    std::uint64_t quotDigit, remainderDigit, prodTwoDigits;
    std::int64_t t, k;
    std::int32_t divisorShift, i, j;

    if(dividentLen < divisorLen || divisorLen <= 0 || divisor[divisorLen - 1] == 0)
        return 1;

    if(divisorLen == 1) {
        k = 0;
        for(j = dividentLen - 1; j >= 0; j--) {
            quotient[j] = (k * b + divident[j]) / divisor[0];
            k = (k * b + divident[j]) - quotient[j] * divisor[0];
        }
        if(&remainder != NULL)
            remainder[0] = k;
        return 0;
    }

    divisorShift = nlz(divisor[divisorLen - 1]);

    for(i = divisorLen - 1; i > 0; i--)
        normalDivisor[i] = (divisor[i] << divisorShift) | (static_cast<std::uint64_t>(divisor[i - 1]) >> (32 - divisorShift));
    normalDivisor[0] = divisor[0] << divisorShift;
    normalDividend[dividentLen] = static_cast<std::uint64_t>(divident[dividentLen - 1]) >> (32 - divisorShift);
    for(i = dividentLen - 1; i > 0; i--)
        normalDividend[i] = (divident[i] << divisorShift) | (static_cast<std::uint64_t>(divident[i - 1]) >> (32 - divisorShift));
    normalDividend[0] = divident[0] << divisorShift;

    for(j = dividentLen - divisorLen; j >= 0; j--) {
        quotDigit = (normalDividend[j + divisorLen] * b + normalDividend[j + divisorLen - 1]) / normalDivisor[divisorLen - 1];
        remainderDigit = (normalDividend[j + divisorLen] * b + normalDividend[j + divisorLen - 1]) - quotDigit * normalDivisor[divisorLen - 1];

        divmnu_helper_recursive(quotDigit, b, normalDivisor, divisorLen, remainderDigit, normalDividend, j);

        k = 0;
        for(i = 0; i < divisorLen; i++) {
            prodTwoDigits = quotDigit * normalDivisor[i];
            t = normalDividend[i + j] - k - (prodTwoDigits & 0xFFFFFFFF);
            normalDividend[i + j] = t;
            k = (prodTwoDigits >> 32) - (t >> 32);
        }
        t = normalDividend[j + divisorLen] - k;
        normalDividend[j + divisorLen] = t;

        quotient[j] = quotDigit;
        if(t < 0) {
            quotient[j] = quotient[j] - 1;
            k = 0;
            for(i = 0; i < divisorLen; i++) {
                t = static_cast<std::uint64_t>(normalDividend[i + j]) + normalDivisor[i] + k;
                normalDividend[i + j] = t;
                k = t >> 32;
            }
            normalDividend[j + divisorLen] = normalDividend[j + divisorLen] + k;
        }
    }
    if(&remainder != NULL) {
        for(i = 0u; i < divisorLen - 1; i++)
            remainder[i] = (normalDividend[i] >> divisorShift) | (static_cast<std::uint64_t>(normalDividend[i + 1]) << (32 - divisorShift));
        remainder[divisorLen - 1] = normalDividend[divisorLen - 1] >> divisorShift;
    }
    return 0;
}
} // namespace oiak
