#pragma once
#include "bank.hpp"
#include "status.hpp"
#include <string>


/*
 * Main conteiner and manager of Bank. Responsible for create, delete and modify
 */
class CentralBank {
    std::vector<Bank> banks;

    public:


    /*
     * @brief Main constructor of a Central Bank
     *
     * @param data_file_name: the file name where Centralbank save its Data Base.
     */
    CentralBank() = default;


    /*
     * Save the database in a file in binary mode, create on if not exist
     */
    void save();

    //Getters
    Bank* getBank(std::string id);
    std::vector<Bank>& getBankData() {return this->banks;}

    size_t getBankN() const {return banks.size();};

    //Operações
    Status openBank(std::string id);


    bool loadBank(Bank& b) {
        if(getBank(b.getID()) == nullptr) {
            banks.push_back(b);
            return true;
        }
        return false;
    }
};
