#pragma once
#include <cstddef>
#include <string>
#include <variant>
#include <vector>
#include "bank_status.hpp"
#include "money.hpp"


enum Operation {
    OPEN_BANK,
    OPEN_ACCONT,
    CHECK_BALANCE,
    NEW_COIN,
    PAYMENT,
    DEPOSIT,
    TRANSFERENCE
};


namespace payload {
    struct Deposit {
        cents value;
        MoneyType mt_;
        std::string to_id;
    };
    struct Trasference {
        cents value;
        MoneyType mt_;
        std::string to_id;
        std::string from_id;
    };
    struct Pay {
        cents value;
        MoneyType mt_;
        std::string from_id;
    };
    struct Bank {
        std::string id;
        size_t accountN;
    };
}

using PayloadVariant = std::variant<
    std::string,
    MoneyType,
    Money,
    std::vector<Money>,
    payload::Deposit,
    payload::Pay,
    payload::Trasference
>;

struct BasePayLoad {
    Operation operation;
    Status status;
    PayloadVariant payload;
};
