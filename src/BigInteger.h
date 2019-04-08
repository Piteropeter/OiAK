#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

namespace oiak {

class BigInteger {
	bool sign = false;
	std::vector<std::uint32_t> storage = std::vector<std::uint32_t>(1, 0);


public:
	BigInteger() = default;
	BigInteger(std::int32_t);
	BigInteger(std::uint32_t);
	BigInteger(std::int64_t); 
	BigInteger(std::uint64_t);
	//BigInteger(std::string); // TODO: ADD IT LATER
	
	BigInteger& operator=(const BigInteger& b);
	BigInteger& operator+(const BigInteger& b);

	bool get_sign();

	void print();
	std::string get_value();
};

} // namespace oiak
