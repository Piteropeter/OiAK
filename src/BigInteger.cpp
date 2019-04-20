#include "BigInteger.h"

namespace oiak {

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

// OPERATORS

std::uint32_t BigInteger::operator[](std::size_t i) {
    return storage[i];
}

const std::uint32_t BigInteger::operator[](std::size_t i) const {
    return storage[i];
}

BigInteger& BigInteger::operator=(const BigInteger& b) {
    storage = b.storage;
    return *this;
}

BigInteger& BigInteger::operator+(const BigInteger& b) {
    std::uint64_t tmp = 0;
    bool carry_bit = false;

    if(storage.size() < b.storage.size())
        storage.resize(b.storage.size());

    for(auto i = 0u; i < storage.size(); i++) {
        if(i < b.storage.size())
            tmp = static_cast<std::uint64_t>(storage[i]) + static_cast<std::uint64_t>(b.storage[i]);
        else
            tmp = static_cast<std::uint64_t>(storage[i]);

        if(carry_bit) {
            tmp++;
            carry_bit = false;
        }

        if(tmp > UINT32_MAX) {
            storage[i] = tmp << 32 >> 32;
            if(i + 1 == storage.size())
                storage.resize(storage.size() + 1);
            carry_bit = true;

        } else
            storage[i] = static_cast<std::uint32_t>(tmp);
    }
    return *this;
}

BigInteger& BigInteger::operator-(const BigInteger& b) {
    std::uint64_t tmp = 0;
    bool borrow_bit = false;

    if(storage.size() < b.storage.size())
        storage.resize(b.storage.size());

    for(auto i = 0u; i < storage.size(); i++) {




    }
    return *this;
}

// OTHER FUNCTIONS

bool BigInteger::get_sign() const {
    return sign;
}

std::size_t BigInteger::size() const {
    return storage.size();
}

std::string transform_to_decimal(const std::string& hex_string) {
    std::string str(hex_string.size() * 2, '0');

    return str;
}

std::string BigInteger::to_string() {
    // std::stringstream ss;
    // for(auto i = 0u; i < storage.size(); i++) {
    //	for(auto j = 0u; j < 8; j++) {
    //	//char character = storage[i]
    //		//ss << std::hex << /*static_cast<char>*/(storage[i] << 28 - j*4 >> 28 - j*4);
    //		ss << std::hex << /*static_cast<char>*/(storage[i] << 28 - j*4 >> 28 - j*4);
    //	}
    //	//ss << std::hex << storage[i];
    //}
    // return ss.str();

    std::stringstream ss;
    if(sign)
        ss << '-';
    for(auto it = storage.crbegin(); it != storage.crend(); it++)
        ss /*<< std::hex*/ << *it;
    return ss.str();

    // return transform_to_decimal(ss.str());
}
} // namespace oiak
