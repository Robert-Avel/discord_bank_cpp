#pragma once
#include "bank.hpp"
#include "bank_status.hpp"
#include <string>

class CentralBank {
    std::string data_file_name;

    std::vector<Bank> banks;

    public:
    CentralBank(std::string data_file_name);
    ~CentralBank();

    //Getters
    Bank* getBank(std::string id);

    //Operações
    //Criação
    Status openBank(std::string id);
    Status openAccont(std::string bank_id, std::string accont_id);
    Status newMoney(std::string bank_id, std::string money_id, std::string money_symbol);


    //Transação
    Status pay(
        std::string bank_id,
        cents value,
        std::string money_id,
        std::string from_id
    );
    Status deposit(
        std::string bank_id,
        cents value,
        std::string money_id,
        std::string to_id
    );
    Status transference(
        std::string bank_id,
        cents value,
        std::string money_id,
        std::string from_id,
        std::string to_id
    );
};
