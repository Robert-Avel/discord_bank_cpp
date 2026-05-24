#pragma once
#include <cstddef>
#include <string>
#include <variant>
#include <vector>
#include "bank_status.hpp"
#include "money.hpp"


enum Operation {
    OPEN_BANK, //OK
    OPEN_ACCONT, //OK
    INFO_BANK, //OK
    INFO_ACCOUNT, //OK
    CHECK_BALANCE,
    NEW_MONEY,
    INFO_MONEY,
    PAYMENT,
    DEPOSIT,
    TRANSFERENCE,
    HIRE_USER,
    FIRE_USER,
    PAY_CLIENT
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
    struct Account {
        std::string id;
        std::string balances;
    };
    struct ImprovisedHire {
        std::string job_name;
        Money salary;
    };
}


enum PayloadType {
    PL_TEXT,
    PL_MONEY_TYPE,
    PL_MONEY,
    PL_BALANCE,
    PL_DEPOSIT,
    PL_PAY,
    PL_TRANSFERENCE,
    PL_BANK,
    PL_ACCOUNT
};


using PayloadVariant = std::variant<
    std::string,
    MoneyType,
    Money,
    std::vector<Money>,
    payload::Deposit,
    payload::Pay,
    payload::Trasference,
    payload::Bank,
    payload::Account,
    payload::ImprovisedHire
>;

struct BasePayLoad {
    Operation operation;
    Status status;
    PayloadVariant payload;
};
