#include "BigInteger.h"
#include "BigDecimal.h"

namespace oiak {

// CONSTRUCTORS

BigDecimal::BigDecimal(BigInteger significand, BigInteger exponent, bool sign) {
    this->significand = significand;
    this->exponent = exponent;
    this->significand.set_sign(sign);
}

BigDecimal::BigDecimal(double value) {
    static_assert(sizeof(double) == 8, "Double is not 8 bytes!");

    if(std::isinf<double>(value) || std::isnan<double>(value))
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
    if(sign)
        significand.set_sign(true);
}

// OPERATORS

// OTHER FUNCTIONS

bool BigDecimal::get_sign() const {
    return significand.get_sign();
}

std::string BigDecimal::to_string(std::uint8_t base) {
    std::stringstream ss;
    ss << significand.to_string() << " * 2 ^ " << exponent.to_string();
    return ss.str();
}
} // namespace oiak
