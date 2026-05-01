#include "money.hpp"
#include <sstream>

std::string Money::format() const {
    std::stringstream buffer;
    buffer << this->_mt.symbol << " " << this->value << " (" << this->_mt.id << ")";
    return buffer.str();
}
