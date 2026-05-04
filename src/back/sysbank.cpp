#include "sysbank.hpp"
#include "bank.hpp"
#include "saver.hpp"
#include <cstdint>
#include <fstream>
#include <ios>

CentralBank::CentralBank(std::string data_file_name) {
    this->data_file_name = data_file_name;

    std::ifstream saver;
    saver.open(data_file_name, std::ios::in | std::ios::binary);
    if(!saver) {return;}

    int32_t bank_n;
    saver.read((char*) &bank_n, sizeof(int32_t));
    for(int i = 0; i < bank_n; i++) {
        Bank b = load::bank(saver);
        this->banks.push_back(b);
    }
}


CentralBank::~CentralBank() {
    std::ofstream saver;
    saver.open(data_file_name, std::ios::out | std::ios::binary | std::ios::trunc);
    if(!saver) {return;}

    int32_t bank_n = banks.size();
    saver.write( (char*) &bank_n, sizeof(int32_t));
    for(Bank b: banks) {
        save::bank(b, saver);
    }
}


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
