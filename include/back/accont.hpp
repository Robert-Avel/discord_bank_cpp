#pragma once
#include "bank_status.hpp"
#include "money.hpp"
#include <vector>

class Account {
    std::string id;
    std::vector<Money> balances;


    Money* _getMoney(std::string money_id);

    public:
    Account(std::string id_);

    const Money* getMoney(std::string money_id);
    std::string getID() const;
    std::string formatBalance() const;
    const std::vector<Money> getBalances() const;

    const cents getBalance(std::string money_id);
    void addMoney(std::string id, std::string symbol, cents value);
    Status removeMoney(std::string id, cents value);
};
