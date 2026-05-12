#pragma once
#include <optional>
#include <string>
#include <cstdint>
#include "bank_status.hpp"

/*
 * @Client User of SysBank, represent the users of a Bank within CentralBank
 */
class ClientUser {
    std::string global_name;

    std::string user_id;
    std::string bank_id;
    std::optional<uint32_t> account_index;


    public:

    /*
     * @brief Base Constructor of Client User Class
     *
     * @param bank_id: Defines the bank ID of which the account belong to
     * @param global_name: Defines the global name used in interface
     * @param user_id: Unique ID for internal identification
     */
    ClientUser(const std::string& bank_id, const std::string& global_name, const  std::string& user_id) {
        this->global_name = global_name;
        this->user_id = user_id;
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
     * Returns the Bank ID of Client
     */
    const std::string& getBankID() const {return this->bank_id;}

    /*
     * Returns a pointer of the index of its account in Bank, returns nullptr if the client has no account
     */
    const uint32_t* getAccountIndex() const {
        if(this->account_index.has_value()) {return &account_index.value();}
        return nullptr;
    }


    ~ClientUser();

    /*
     * @brief After the creation of an account, it may be linked with the Client, allowing fast acess
     */
    Status linkAccount(uint32_t index);

    /*
     * @brief Unlink with an account already created
     */
    Status unlinkAccount();

    /*
     * @brief Set a new Global Name
     *
     * @param new_g_n: New Global Name to set
     */
    void setGlobalName(const std::string& new_g_n) {this->global_name = new_g_n;}
};
