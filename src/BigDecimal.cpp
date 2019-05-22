#include "BigInteger.h"
#include "BigDecimal.h"

namespace oiak {

// CONSTRUCTORS

BigDecimal::BigDecimal(BigInteger significand, BigInteger exponent, bool sign) {
    this->significand = significand;
    this->exponent = exponent;
    this->sign = sign;
}

BigDecimal::BigDecimal(double value) {
    char xd[4];
    static_assert(sizeof(double) == 8, "Double is not 8 bytes!");
    // std::uint64_t storage = reinterpret_cast<std::uint64_t>(value);
    std::uint8_t* storage = reinterpret_cast<std::uint8_t*>(&value);
    sign = storage[7] >> 7;
	exponent = BigInteger(static_cast<std::uint32_t>(storage[7] << 1 >> 1) + static_cast<std::uint32_t>(storage[6]) >> 4);
    // exponent = BigInteger(*(storage+1) - *(storage + 11));
    // exponent = BigInteger(storage << 1 >> 53);
    // significand = BigInteger(*(storage+12));
    // significand = BigInteger(storage << 12 >> 12);

    for(auto i = 0; i < 8; i++)
        std::cout << std::hex << std::uint32_t(storage[i]) << "\n";
}

// OPERATORS

// OTHER FUNCTIONS

bool BigDecimal::get_sign() const {
    return sign;
}

std::string BigDecimal::to_string(std::uint8_t base) {
    std::stringstream ss;
    if(sign)
        ss << '-';
    ss << significand.to_string() << " * 10 ^ " << exponent.to_string();
    return ss.str();
}

} // namespace oiak
