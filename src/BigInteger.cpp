#include "BigInteger.h"

namespace oiak {

// CONSTRUCTORS

void BigInteger::normalize() {
    if(storage.back() == 0) {
        auto it = storage.begin() + storage.size() - 1;
        while(*it == 0 && it != storage.end()) {
            storage.erase(it);
            it = storage.begin() + storage.size() - 1;
        }
    }
}

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

BigInteger& BigInteger::operator+(const BigInteger& b) {
    if(!sign && !b.sign) {
        storage = add(storage, b.storage);
        return *this;
    }

    // Zero! Mo¿e zmiana reprezentacji znaku dla ³atwiejszej obs³ugi?
    int cmp = compareStorage(storage, b.storage);
    if(cmp == 0) {
        storage.clear();
        return *this;
    }

    if(cmp > 0) {
        storage = subtract(storage, b.storage);
        sign = false;
    } else {
        storage = subtract(b.storage, storage);
        sign = true;
    }

    return *this;
}

BigInteger& BigInteger::operator-(const BigInteger& b) {
    if(b.sign != sign) {
        storage = add(storage, b.storage);
        return *this;
    }

	int cmp = compareStorage(storage, b.storage);
    if(cmp == 0)
        storage.clear();

	if(cmp > 0) {
        storage = subtract(storage, b.storage);
        sign = false;
        return *this;
	} else {
        storage = subtract(b.storage, storage);
		sign = true;
        return *this;
	}
}

BigInteger& BigInteger::operator*(const BigInteger& b) {
    std::vector<std::uint64_t> tmp(storage.size() + b.storage.size(), 0);

    for(auto i = 0u; i < storage.size(); i++) {
        for(auto j = 0u; j < b.storage.size(); j++) {
            tmp[i + j] += static_cast<std::uint64_t>(storage[i]) * static_cast<std::uint64_t>(b.storage[j]);
            if(tmp[i + j] > UINT32_MAX) {
                tmp[i + j + 1] += tmp[i + j] >> 32;
                tmp[i + j] = tmp[i + j] << 32 >> 32;
            }
        }
    }

    storage.resize(tmp.size());
    for(auto i = 0u; i < storage.size(); i++) {
        storage[i] = static_cast<std::uint32_t>(tmp[i]);
    }

    if(sign && !b.sign || !sign && b.sign)
        sign = true;
    else
        sign = false;

    normalize();
    return *this;
}

BigInteger& BigInteger::operator/(const BigInteger& b) {
    BigInteger tmp;

    if(*this < b)
        *this = tmp;
    else {
        // auto rbegin = b.storage.rbegin();
        // auto rend = b.storage.rbegin() + b.size;
        // tmp = BigInteger(rbegin, rend);

        if(sign && !b.sign || !sign && b.sign)
            sign = true;
        else
            sign = false;
    }
    return *this;
}

bool BigInteger::operator<(const BigInteger& b) const {
    if(storage.size() < b.storage.size())
        return true;
    else if(storage.size() > b.storage.size())
        return false;
    else {
        if(storage.back() < b.storage.back())
            return true;
        else
            return false;
    }
}

bool BigInteger::operator>(const BigInteger& b) const {
    if(storage.size() > b.storage.size())
        return true;
    else if(storage.size() < b.storage.size())
        return false;
    else {
        if(storage.back() > b.storage.back())
            return true;
        else
            return false;
    }
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

//std::string transform_to_decimal(const std::string& hex_string) {
//    std::string str(hex_string.size() * 2, '0');
//
//    return str;
//}

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
int BigInteger::compareStorage(std::vector<std::uint32_t> s1, std::vector<std::uint32_t> s2) {
    auto len1 = s1.size();
    auto len2 = s2.size();

	if(len1 < len2) 
        return -1;
    if(len1 > len2)
        return 1;
    int i = (len1 - 1);

	while(i>=0) {
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
std::vector<std::uint32_t> BigInteger::add(std::vector<std::uint32_t> s1, std::vector<std::uint32_t> s2) {
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
std::vector<std::uint32_t> BigInteger::subtract(std::vector<std::uint32_t> s1, std::vector<std::uint32_t> s2) {
	 std::int64_t tmp = 0;
	 bool borrow_bit = false;

	 auto result = std::vector<std::uint32_t>(s1);

	 auto s1Size = s1.size();
     auto s2Size = s2.size();

     for(auto i = 0u; i < s1Size; i++) {
         if(i < s2Size)
             tmp = static_cast<std::int64_t>(s1[i]) - static_cast<std::int64_t>(s2[i]);
         else
             tmp = static_cast<std::int64_t>(s1[i]);

         if(borrow_bit) {
             tmp--;
             borrow_bit = false;
         }

         if(tmp < 0) {
             result[i] = (static_cast<std::int64_t>(UINT32_MAX) + tmp) >> 32;
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



} // namespace oiak
