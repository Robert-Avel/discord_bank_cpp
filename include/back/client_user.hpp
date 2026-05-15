#pragma once
#include <string>
#include "accont.hpp"
#include "bank_status.hpp"
#include <unordered_map>

/*
 * @Client User of SysBank, represent the users of a Bank within CentralBank
 */
class ClientUser {
    std::string global_name;

    std::string user_id;
    std::string bank_id;
    std::unordered_map<std::string, Account&> accounts;


    public:

    /*
     * @brief Base Constructor of Client User Class
     *
     * @param bank_id: Defines the bank ID of which the account belong to
     * @param global_name: Defines the global name used in interface
     * @param user_id: Unique ID for internal identification
     */
    ClientUser(const std::string& bank_id, const std::string& global_name, const  std::string& user_id): user_id(user_id) {
        this->global_name = global_name;
        this->bank_id = bank_id;
    }

    /*
     * Returns the Global Name of Client
     */
    const std::string& getGlobalName() const {return this->global_name;}

    /*
     * Returns the User ID of Client
     */
    const std::string& getUserID() const {return this->user_id;}

    /*
     * Returns the Bank ID of Bank
     */
    const std::string& getBankID() const {return this->bank_id;}

    /*
     * Returns a pointer of the index of its account in Bank, returns nullptr if the client has no account
     */
    Account* getAccount(const std::string& bank_id) const {
        auto it = accounts.find(bank_id);
        if(it == accounts.end()) {
            return nullptr;
        }
        return &it->second;
    }


    /*
     * @brief After the creation of an account, it may be linked with the Client, allowing fast acess
     *
     * @param a: Account object
     */
    Status linkAccount(Account& a, const std::string& bank_id);

    /*
     * @brief Unlink with an account already created
     */
    Status unlinkAccount(const std::string& bank_id);

    /*
     * @brief Set a new Global Name
     *
     * @param new_g_n: New Global Name to set
     */
    void setGlobalName(const std::string& new_g_n) {this->global_name = new_g_n;}
};
