#include "Utilities.h"

namespace oiak {

void print(const std::vector<std::uint8_t>& storage) {
    for(auto& x : storage)
        std::cout << x;
}

} // namespace oiak
