#include "central_bank.hpp"
#include "bank.hpp"
#include "bank_status.hpp"
#include "saver.hpp"


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
