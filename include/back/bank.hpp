#pragma once
#include "accont.hpp"
#include "bank_status.hpp"
#include "money.hpp"

class Bank {
    std::string id;
    std::vector<Account> acconts;
    std::vector<MoneyType> white_list_money;

    //Getter interno
    Account* _getAccont(const std::string id);

    public:
    //Construto
    Bank(std::string id);

    //Getter Externo
    std::string getID() const;
    size_t getAccontN() const;
    Account* getAccont(const std::string id);
    const std::vector<Account> getAccounts() const;
    const std::vector<MoneyType> getWhiteListMoney() const;

    //Operação de moeda
    Status moneyNew(std::string id, std::string symbol);
    MoneyType* getMoney(std::string id);

    //Operação de Conta
    Status openAccont(std::string id);

    Status deposit(Account* to, cents value, std::string money_id, std::string money_symbol);
    Status depositWhiteList(Account* to, cents value, std::string money_id);
    Status pay(Account* from, cents value, std::string money_id);
    Status transference(
        Account* from,
        Account* to,
        cents value,
        std::string money_id,
        std::string money_symbol
    );

    //Loader
    Status loadAccount(const Account& a);


};
