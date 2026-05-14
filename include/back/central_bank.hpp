#pragma once
#include "bank.hpp"
#include "bank_status.hpp"
#include <string>


/*
 * Main conteiner and manager of Bank. Responsible for create, delete and modify
 */
class CentralBank {
    std::vector<Bank> banks;

    public:
    std::string data_file_name;


    /*
     * @brief Main constructor of a Central Bank
     *
     * @param data_file_name: the file name where Centralbank save its Data Base.
     */
    CentralBank(std::string data_file_name);


    /*
     * Save the database in a file in binary mode, create on if not exist
     */
    void save();

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
