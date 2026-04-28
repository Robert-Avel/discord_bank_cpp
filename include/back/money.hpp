#pragma once
#include <string>
#include <cstdint>

typedef uint32_t cents;

struct MoneyType {
    std::string id;
    std::string symbol;
};

struct Money {
    MoneyType _mt;
    cents value;

    std::string format();
};
