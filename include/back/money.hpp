#pragma once
#include <string>
#include <cstdint>

typedef uint32_t cents;

/*
 * @brief Money Type Unity struct
 *
 * @field id: main Name of Money
 * @field symbol: the simbol that represent that Money;
 */
struct MoneyType {
    std::string id;
    std::string symbol;

    /*
     * @brief Get a Formated String of the money in format "id(symbol)"
     *
     * @return: A Formated String of struct
     */
    std::string format() const;

};

/*
 * @brief: Represent a monetary value of any Money Type
 *
 * @field _mt: The MoneyType struct of money
 * @field value: The actual value of monetary value
 */
struct Money {
    MoneyType _mt;
    cents value;

    /*
     * @brief Get a Formated String of the monetary value in format "_mt.symbol value (_mt.id)"
     *
     * @return: A Formated String of struct
     */
    std::string format() const;
};
