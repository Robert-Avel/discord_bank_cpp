#pragma once
#include "bank.hpp"

class CentralBank {
    std::string data_file_name;

    std::vector<Bank> banks;

    public:
    CentralBank(std::string data_file_name);
    ~CentralBank();


    Bank* getBank(std::string id);
    Status openBank(std::string id);
    Status openAccont(std::string bank_id, std::string accont_id);
};
