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
    static_assert(sizeof(double) == 8, "Double is not 8 bytes!");

    if(std::isinf<double>(value) || std::isnan<double>(value))
        throw std::runtime_error("Double infinite or NaN!");

    std::uint8_t* storage = reinterpret_cast<std::uint8_t*>(&value);
    sign = storage[7] >> 7;

    // clang-format off
    std::uint32_t exp = ((static_cast<std::uint32_t>(storage[7]) << 1 >> 1) << 4) +
                        (static_cast<std::uint32_t>(storage[6]) >> 4);
    std::uint64_t sig = (static_cast<std::uint64_t>(storage[6] << 4 >> 4) << 48) +
                        (static_cast<std::uint64_t>(storage[5]) << 40) +
                        (static_cast<std::uint64_t>(storage[4]) << 32) +
                        (static_cast<std::uint64_t>(storage[3]) << 24) +
                        (static_cast<std::uint64_t>(storage[2]) << 16) +
                        (static_cast<std::uint64_t>(storage[1]) << 8) +
                        (static_cast<std::uint64_t>(storage[0]));
    // clang-format on

    // std::cout << "\nSIG: " << std::hex << sig << std::endl;               // Useful in debugging, will be remover later
	sig += 0x0010000000000000;
    sig = sig << 11 >> 11;
    exp = exp << 21 >> 21;

    exp -= 1075; // 1023 + 52
    // std::cout << "\nSIG2: " << std::hex << sig << std::endl;              // Useful in debugging, will be remover later

    while((sig & 1) == 0) {
        sig >>= 1;
        exp++;
    }
    exponent = BigInteger(static_cast<std::int32_t>(exp));

    significand = BigInteger(sig);

    // for(auto i = 0; i < 8; i++)                                           // Useful in debugging, will be remover later
    //    std::cout << std::hex << std::uint32_t(storage[i]) << "\n";        //
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
    ss << significand.to_string() << " * 2 ^ " << exponent.to_string();
    return ss.str();
}
} // namespace oiak
