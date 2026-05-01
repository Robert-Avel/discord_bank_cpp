#pragma once
#include <string>
#include <cstdint>

typedef uint32_t cents;

struct MoneyType {
    std::string id;
    std::string symbol;

    std::string format() const;

};

struct Money {
    MoneyType _mt;
    cents value;

    std::string format() const;
};
