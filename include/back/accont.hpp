#pragma once
#include "money.hpp"
#include <vector>

class Account {
    std::string id;
    std::vector<Money> balances;


    Money* _getMoney(std::string money_id);

    public:
    Account(std::string id_);

    std::string getID() const;
    std::string formatBalance() const;

    const cents getBalance(std::string money_id);
    void addMoney(std::string id, std::string symbol, cents value);
    bool removeMoney(std::string id, cents value);
};
