#pragma once
#include "bank.hpp"

class CentralBank {
    std::vector<Bank> banks;

    public:
    CentralBank(): banks() {}

    Bank* getBank(std::string id);
    Status openBank(std::string id);
    Status openAccont(std::string bank_id, std::string accont_id);
};
