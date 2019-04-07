#include "BigInteger.h"

namespace oiak {

// CONSTRUCTORS
// No other constructors are needed thanks to implicit conversion

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

BigInteger::BigInteger(std::int64_t value)
{
	if(value < 0) {
		sign = true;
		value *= -1;
	}
	if(value > UINT32_MAX || value < -UINT32_MAX) {
		storage.resize(2);

		storage[1] = value >> 32;
		storage[0] = value << 32 >> 32;
	}
}

BigInteger::BigInteger(std::uint64_t value)
{
	if(value > UINT32_MAX) {
		storage.resize(2);

		storage[1] = value >> 32;
		storage[0] = value << 32 >> 32;
	}
}

// OTHER FUNCTIONS

bool BigInteger::get_sign()
{
	return sign;
}

void BigInteger::print() {
    std::cout << get_value();
}

std::string BigInteger::get_value() {
	std::stringstream ss;
	if(sign)
		ss << '-';
	for(auto it = storage.crbegin(); it != storage.crend(); it++)
		ss << *it;
	return ss.str();
}
} // namespace oiak
