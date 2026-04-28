#pragma once
#include "accont.hpp"
#include "bank_status.hpp"

class Bank {
    std::string id;
    std::vector<Account> acconts;
    std::vector<MoneyType> white_list_money;

    Account* _getAccont(const std::string id);

    public:
    Bank(std::string id);

    std::string getID() const;
    size_t getAccontN() const;

    const Account* getAccont(const std::string id);


    Status deposit(cents value, std::string money_id, std::string money_symbol, std::string to_id);


    Status pay(cents value, std::string money_id, std::string money_symbol, std::string from_id);


    Status openAccont(std::string id);

    Status transference(
        cents value,
        std::string money_id,
        std::string money_symbol,
        std::string from_id,
        std::string to_id
    );
};
