#include "sysbank.hpp"
#include "bank.hpp"

CentralBank::CentralBank(): banks() {}

Bank* CentralBank::getBank(std::string id) {
    for(Bank& b: banks) {
        if(b.getID() == id) {
            return &b;
        }
    }
    return nullptr;
}

Status CentralBank::openBank(std::string id) {
    if(getBank(id) == nullptr) {
        banks.push_back(
            Bank{id}
        );
        return SUCCESS;
    }
    return ALREADY_EXIST;
}

Status CentralBank::openAccont(std::string bank_id, std::string accont_id) {
    Bank* b = this->getBank(bank_id);
    if(b == nullptr) {return NOT_FOUND;}

    return b->openAccont(accont_id);
}
