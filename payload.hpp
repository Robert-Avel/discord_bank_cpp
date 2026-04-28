#pragma once
#include <cstddef>
#include <string>
#include <cstdint>
#include <variant>
#include <vector>
typedef uint32_t cents;


struct MoneyType {
    std::string id;
    std::string symbol;
};

struct Money {
    MoneyType _mt;
    cents value;
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


struct PayLoad {
    std::string operation;
    std::string status;
    std::string message;
    std::variant<
        std::string,
        MoneyType,
        Money,
        std::vector<Money>,
        payload::Deposit,
        payload::Pay,
        payload::Trasference
    > payload;
};
