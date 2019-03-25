#pragma once
#include <cmath>
#include <vector>
#include <iostream>

namespace oiak {

template <unsigned char base>
std::size_t needed_digits(int value) {
    std::size_t digits = 1u;
    while((value % static_cast<int>(std::pow(base, digits))) != value) {
        // std::cout << "Modulo: " << (value % static_cast<int>(std::pow(base, digits))) << std::endl;
        ////std::cout << "Mnozenie: " << (digits * base) << std::endl;
        digits++;
    }
    return digits;
}

void print(const std::vector<std::uint8_t>& storage);

template <unsigned char base>
std::size_t get_digit(int value, int index) {
    std::size_t sum = 0;
    for(auto i = 0u; i < index; i++) {
		
	}
    /*return static_cast<std::size_t>(value % static_cast<int>(std::pow(base, i+1))*/
}

} // namespace oiak
