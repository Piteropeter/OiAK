#include "BigInteger.h"
#include "BigDecimal.h"

namespace oiak {

// CONSTRUCTORS

BigDecimal::BigDecimal(BigInteger significand, BigInteger exponent, bool sign) {
    this->significand = significand;
    this->exponent = exponent;
    this->significand.set_sign(sign);
    normalize(*this);
}

BigDecimal::BigDecimal(double value) {
    static_assert(sizeof(double) == 8, "Double is not 8 bytes!");

    if(std::isinf(value) || std::isnan(value))
        throw std::runtime_error("Double infinite or NaN!\n");

    std::uint8_t* bytes_array = reinterpret_cast<std::uint8_t*>(&value);
    std::uint64_t storage = 0;
    // clang-format off
    storage = (static_cast<std::uint64_t>(bytes_array[7]) << 56) +
              (static_cast<std::uint64_t>(bytes_array[6]) << 48) +
              (static_cast<std::uint64_t>(bytes_array[5]) << 40) +
              (static_cast<std::uint64_t>(bytes_array[4]) << 32) +
              (static_cast<std::uint64_t>(bytes_array[3]) << 24) +
              (static_cast<std::uint64_t>(bytes_array[2]) << 16) +
              (static_cast<std::uint64_t>(bytes_array[1]) << 8) +
              (static_cast<std::uint64_t>(bytes_array[0]));
    // clang-format on

    int32_t exp = (storage >> 52ull) & 0x7ffull;
    uint64_t sig = exp == 0u ? storage & ((1ull << 52ull) - 1ull) << 1ull : storage & (1ull << 52ull) - 1ull | 1ull << 52ull;

    exp -= 1075; // 1023 + 52

    if(sig == 0) {
        exponent = BigInteger(0);
        significand = BigInteger(0);
        return;
    }

    while((sig & 1) == 0) {
        sig >>= 1;
        exp++;
    }

    exponent = BigInteger(exp);
    significand = BigInteger(sig);
    significand.set_sign(bytes_array[7] >> 7);
    normalize(*this);
}

BigDecimal::BigDecimal(std::string str) {
    bool sign = false;
    if(str[0] == '-') {
        sign = true;
        str = str.substr(1, str.size());
    }
    bool is_dot_present = str.find('.') != std::string::npos;
    if(is_dot_present) {
        std::int32_t offset = 0;

        for(auto it = str.rbegin(); *it != '.'; it++)
            offset++;

        str.erase(str.find('.'), 1);

        significand = BigInteger(str);
        exponent = BigInteger(offset * -4);
    } else {
        significand = BigInteger(str);
        exponent = BigInteger(0);
    }
    while(!(significand[0] % 2)) {
        significand = significand / BigInteger(2);
        exponent = exponent + BigInteger(1);
    }
    if(sign)
        significand.set_sign(true);

    normalize(*this);
}

// OPERATORS

BigDecimal& BigDecimal::operator=(const BigDecimal& b) {
    significand = b.significand;
    exponent = b.exponent;
    return *this;
}

BigDecimal BigDecimal::operator+(const BigDecimal& b) {
    BigDecimal new_decimal = *this;
    BigDecimal temp;

    if(new_decimal.exponent > b.exponent) {
        while(new_decimal.exponent > b.exponent) {
            new_decimal.significand = new_decimal.significand * BigInteger(2);
            new_decimal.exponent = new_decimal.exponent - BigInteger(1);
        }

        new_decimal.significand = new_decimal.significand + b.significand;
    } else if(new_decimal.exponent < b.exponent) {
        temp = b;
        while(new_decimal.exponent < temp.exponent) {
            temp.significand = temp.significand * BigInteger(2);
            temp.exponent = temp.exponent - BigInteger(1);
        }

        new_decimal.significand = new_decimal.significand + temp.significand;
    } else {
        new_decimal.significand = new_decimal.significand + b.significand;
    }

    normalize(new_decimal);
    return new_decimal;
}

BigDecimal BigDecimal::operator-(const BigDecimal& b) {
    BigDecimal new_decimal = *this;
    BigDecimal temp;

    if(new_decimal.exponent > b.exponent) {
        while(new_decimal.exponent > b.exponent) {
            new_decimal.significand = new_decimal.significand * BigInteger(2);
            new_decimal.exponent = new_decimal.exponent - BigInteger(1);
        }

        new_decimal.significand = new_decimal.significand - b.significand;
    } else if(new_decimal.exponent < b.exponent) {
        temp = b;
        while(new_decimal.exponent < temp.exponent) {
            temp.significand = temp.significand * BigInteger(2);
            temp.exponent = temp.exponent - BigInteger(1);
        }

        new_decimal.significand = new_decimal.significand - temp.significand;
    } else {
        new_decimal.significand = new_decimal.significand - b.significand;
    }

    normalize(new_decimal);
    return new_decimal;
}

BigDecimal BigDecimal::operator*(const BigDecimal& b) {
    BigDecimal new_decimal = *this;

    new_decimal.significand = new_decimal.significand * b.significand;
    new_decimal.exponent = new_decimal.exponent + b.exponent;

    normalize(new_decimal);
    return new_decimal;
}

BigDecimal BigDecimal::operator/(const BigDecimal& b) {
    return this->divide(b, BigInteger(64), Round::symetric_even);
}

BigDecimal BigDecimal::divide(const BigDecimal& b, BigInteger precision, BigDecimal::Round roundigMode) {
    if(significand == 0)
        return BigDecimal("0.0");
    BigInteger one = BigInteger(1);
    BigDecimal new_decimal = *this;

    auto precA = new_decimal.significand.size() * 32 - new_decimal.significand.nlz(new_decimal.significand.storage.back());
    auto precB = b.significand.size() * 32 - b.significand.nlz(b.significand.storage.back());

    // * 4, bo jedna cyfra hex kodowana przez 4 cyfry bin
    auto desiredPrec = precision * BigInteger(4) + BigInteger(precB - 1);
    auto newPrec = desiredPrec - precA;

    for(auto i = BigInteger(0); i < newPrec; i = i + one) {
        new_decimal.significand = new_decimal.significand * BigInteger(2);
        new_decimal.exponent = new_decimal.exponent - one;
    }
    new_decimal.exponent = new_decimal.exponent - b.exponent;

    auto remainder = new_decimal.significand.divide(b.significand);

    for(auto i = BigInteger(0); i < 32; i = i + one) {
        remainder = remainder * BigInteger(2);
    }

    remainder = remainder / b.significand;

    std::uint32_t rs = remainder[remainder.size() - 1] << (remainder.nlz(remainder.storage.back()) / 4);
    std::uint32_t r = static_cast<std::uint64_t>(rs) >> 31 << 1;
    std::uint32_t s = (rs & 0x7FFFFFFFFFFFFFF) != 0 ? 1 : 0;
    rs = r + s;

    switch(roundigMode) {
    case Round::ceil:
        if(!new_decimal.get_sign())
            new_decimal.significand = new_decimal.significand + one;
        break;
    case Round::floor:
        if(new_decimal.get_sign())
            new_decimal.significand = new_decimal.significand - one;
        break;
    case Round::symetric_even:
        if(rs == 3)
            new_decimal.significand = new_decimal.significand + BigInteger(1);
        else if(rs == 2) {
            if(new_decimal.significand[0] % 2)
                new_decimal.significand = new_decimal.significand + BigInteger(1);
        }
        break;
    case Round::cut:
        break;
    default:
        break;
    }

    normalize(new_decimal);
    return new_decimal;
}

// OTHER FUNCTIONS

bool BigDecimal::get_sign() const {
    return significand.get_sign();
}

std::string BigDecimal::to_string() {
    std::stringstream ss;
    BigInteger significand = this->significand;
    BigInteger exponent = this->exponent;

    while(exponent[0] % 4) {
        significand = significand * BigInteger(2);
        exponent = exponent - BigInteger(1);
    }
    std::string basic_string = significand.to_string();
    std::int64_t offset = 0;

    if(exponent < BigInteger(0)) {
        while(!(exponent == BigInteger(0))) {
            offset++;
            exponent = exponent + BigInteger(4);
        }

        if(offset >= basic_string.size()) {
            while(offset > basic_string.size()) {
                basic_string.insert(basic_string.begin(), '0');
            }
            ss << "0." << basic_string;
        } else {
            basic_string.insert(basic_string.begin() + (basic_string.size() - offset), '.');
            if(basic_string[0] == '.')
                basic_string.insert(basic_string.begin(), '0');
            if(basic_string[0] == '-' && basic_string[1] == '.')
                basic_string.insert(basic_string.begin() + 1, '0');
            ss << basic_string;
        }
    } else if(exponent > BigInteger(0)) {
        while(!(exponent == BigInteger(0))) {
            offset--;
            exponent = exponent - BigInteger(4);
        }

        while(offset < 0) {
            basic_string.push_back('0');
            offset++;
        }
        ss << basic_string;
    } else {
        ss << significand.to_string();
    }

    return ss.str();
}

std::string BigDecimal::to_exponential_notation() {
    std::stringstream ss;
    ss << significand.to_string() << " * 2 ^ " << exponent.to_string();
    return ss.str();
}

void BigDecimal::normalize(BigDecimal& b) {
    if(b.significand.size() == 1 && b.significand[0] == 0)
        b.exponent = BigInteger(0);
    else
        while(!(b.significand[0] % 2)) {
            b.significand = b.significand / BigInteger(2);
            b.exponent = b.exponent + BigInteger(1);
        }
}
} // namespace oiak
